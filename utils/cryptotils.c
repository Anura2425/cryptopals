#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Base64 encoding table
static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Function to convert a hex character to its corresponding value
int hex_to_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1; // Invalid character
}

size_t hex_decode(const char *hex_str, uint8_t **output) {
    /*
    Function to convert a hex string to raw bytes
    Handles both even and uneven length hexadecimal strings
    Input must be in the format: ffe6b or FFE8B
    */
    size_t len = strlen(hex_str);
    size_t byte_len;
    
    // Check if we have an odd number of digits in the hexadecimal string
    int is_odd = (len % 2 != 0); // 1 if its odd, 0 if its even
    
    // Calculate the byte length (adds 1 if the hex string is of an odd length)
    // which allows for one more bytes worth of space in the overall byte_len
    byte_len = len / 2 + (is_odd ? 1 : 0);
    
    // Allocate memory for output 
    *output = (uint8_t *)malloc(byte_len);
    if (*output == NULL){
        // handle memory allocation failure
        return 0;
    }

    size_t i = 0, j = 0;

    // If odd length, handle the first character separately
    if (is_odd) {
        int val = hex_to_int(hex_str[0]);
        // if the character is invalid, return an error and free memory/pointer
        if (val == -1) {
            free(*output);  
            *output = NULL; // clean up memory
            return 0;
        }
        (*output)[0] = val;
        i = 1;
        j = 1;
    }
    
    // Process remaining characters in pairs i.e. 72 6f 6d 
    for (i; i < len; i += 2, j++) {
        // higher hex value and lower hex char
        int high = hex_to_int(hex_str[i]);
        int low = hex_to_int(hex_str[i + 1]);
        // if either of the characters are invalid, return an error and free memory/pointer
        if (high == -1 || low == -1) {
            free(*output);
            *output = NULL;
            return 0;
        }
        // combine the two half-bytes, shift the higher one left 4 bits and or with the lower one
        (*output)[j] = (high << 4) | low;
    }
    return byte_len;
}


char *base64_encode(const uint8_t *data, size_t input_length) {
    /*
    Function to encode raw bytes to base64 string
    */
    size_t output_length = 4 * ((input_length + 2) / 3); // every 3 bytes is 4 characters in base64
    char *encoded_data = (char *)malloc(output_length + 1); // +1 allocates space for null terminator
    if (encoded_data == NULL){
        return NULL;
    } 
    
    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;
        
        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;
        
        encoded_data[j++] = base64_table[(triple >> 18) & 0x3F];
        encoded_data[j++] = base64_table[(triple >> 12) & 0x3F];
        encoded_data[j++] = base64_table[(triple >> 6) & 0x3F];
        encoded_data[j++] = base64_table[triple & 0x3F];
    }
    
    // Add padding if necessary
    for (size_t i = 0; i < (3 - input_length % 3) % 3; i++) {
        encoded_data[output_length - 1 - i] = '=';
    }
    
    encoded_data[output_length] = '\0';
    return encoded_data;
}

void hex_to_base64(const char *hex_string) {
    uint8_t *raw_bytes = NULL;
    
    // handles the case that the input hex string includes the 0x / 0X prefix
    const char *hex_ptr = hex_string;
    if (hex_string[0] == '0' && (hex_string[1] == 'x' || hex_string[1] == 'X')) {
        hex_ptr = hex_string + 2;  // Skip the "0x" prefix
    }

    printf("Input hex string: %s (length: %zu)\n", hex_string, strlen(hex_string));
    
    // Convert hex to raw bytes
    size_t bytes_len = hex_decode(hex_string, &raw_bytes);
    if (bytes_len == 0) {
        printf("Error decoding hex string\n");
        return;
    }
    
    printf("Decoded bytes (hex): ");
    for (size_t i = 0; i < bytes_len; i++) {
        printf("%02x ", raw_bytes[i]);
    }
    printf("\n");
    
    // Convert raw bytes to base64 using base64_encode()
    char *base64_result = base64_encode(raw_bytes, bytes_len);
    if (base64_result == NULL) {
        // output error
        printf("Error encoding to base64\n");
        free(raw_bytes);
        return;
    }
    
    printf("Base64 output: %s\n\n", base64_result);
    
    // Clean up memory
    free(raw_bytes);
    free(base64_result);
}
