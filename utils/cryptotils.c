#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "cryptotils.h"

// Base64 encoding table
static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char hex_table[] = "0123456789abcdef";

// GENERAL Functions
int hex_to_int(char c) {
    /*
    Convert a hex character to its corresponding value
    */
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1; // Invalid character
}

char int_to_hex(int n){
    /*
    Convert an integer value to its corresponding hex character
    */
    return hex_table[n];
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
    for (; i < len; i += 2, j++) {
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

void hex_encode(const char* input, size_t input_len, char* output) {
    static const char hex[] = "0123456789abcdef";
    
    for (size_t i = 0; i < input_len; i++) {
        unsigned char byte = (unsigned char)input[i];
        output[i*2]     = hex[byte >> 4];
        output[i*2 + 1] = hex[byte & 0x0F];
    }
    
    output[input_len * 2] = '\0';  // Null-terminate the string
}

char* xor_binary(const uint8_t* buffer_a, const uint8_t* buffer_b, size_t input_length) {
    uint8_t* result_buffer = (uint8_t*)malloc(input_length);
    if (result_buffer == NULL) {
        return NULL;
    }
    // perform XOR on each value of the two buffers
    for (size_t i = 0; i < input_length; i++) {
        result_buffer[i] = buffer_a[i] ^ buffer_b[i];
    }

    return result_buffer;
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

// CHALLENGE functions
// HextoB64
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
        printf("%02x", raw_bytes[i]);
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

// FixedXOR
void fixed_xor(const char* buffer_a, const char* buffer_b){
    /*
    Takes two hex strings, decodes them, xors the two buffers, 
    encodes the result back into hex (inputs must be same length)
    */
    uint8_t* raw_bytes1 = NULL;
    size_t bytes_len1 = hex_decode(buffer_a, &raw_bytes1);
    printf("Decoded bytes (hex): ");
    for (size_t i = 0; i < bytes_len1; i++) {
        printf("%02x ", raw_bytes1[i]);
    }
    printf("\n");

    uint8_t* raw_bytes2 = NULL;
    size_t bytes_len2 = hex_decode(buffer_b, &raw_bytes2);
    printf("Decoded bytes (hex): ");
    for (size_t i = 0; i < bytes_len2; i++) {
        printf("%02x ", raw_bytes2[i]);
    }
    printf("\n");

    if (bytes_len1 != bytes_len2) {
        printf("Error: the input buffers must be the same length");
        free(raw_bytes1);
        free(raw_bytes2);
        return;
    }

    size_t xor_len = bytes_len1;
    uint8_t* xor_result = xor_binary(raw_bytes1, raw_bytes2, xor_len);
    if (xor_result == NULL) {
        printf("Error performing XOR operation\n");
        free(raw_bytes1);
        free(raw_bytes2);
        return;
    }

    printf("XOR result (hex): ");
    for (size_t i = 0; i < xor_len; i++) {
        printf("%02x ", xor_result[i]);
    }
    printf("\n");

    free(xor_result);
    free(raw_bytes1);
    free(raw_bytes2);
}

// SingleByteXORCipher
int score_text(const char* text, size_t length){
    /*
    iterates through text and scores it based on two factors
    1. characters from the english alphabet add 1 to the score
    2. characters that are a part of the most common english characters add 2 to the score
    Then returns the score
    */
    int score = 0;
    const char* common_letters = "etaoin shrdlu";
    for (size_t i = 0; i < length; i++){
        if (isalpha(text[i]) || isspace(text[i])){
            score++;
        }
        if (strchr(common_letters, tolower(text[i]))){
            score+=2;
        }
    }
    return score;
}

struct scoring_data single_byte_xor(const char* hex_string) {
    struct scoring_data result = {NULL, 0, 0};
    uint8_t* raw_bytes = NULL;
    size_t bytes_length = hex_decode(hex_string, &raw_bytes);
    
    if (bytes_length == 0 || raw_bytes == NULL) {
        printf("Error: Failed to decode hex string\n");
        return result;
    }
    
    int best_score = 0;
    int best_key = 0;
    char* temp_buffer = (char*)malloc(bytes_length + 1);
    
    if (temp_buffer == NULL) {
        printf("Error: Memory allocation failed\n");
        free(raw_bytes);
        return result;
    }
    
    // iterate through all possible 256 (0 - 255) one byte key possiblities and XOR
    for (int key = 0; key < 256; key++) {
        // Apply XOR with current key
        for (int i = 0; i < bytes_length; i++) {
            temp_buffer[i] = raw_bytes[i] ^ key;
        }
        temp_buffer[bytes_length] = '\0';
        
        //score each output, save the highest score output and key
        int current_score = score_text(temp_buffer, bytes_length);
        if (current_score > best_score) {
            best_score = current_score;
            best_key = key;
        }
    }
    
    // Now that we know the best key, generate the final result
    char* decrypted = (char*)malloc(bytes_length + 1);
    if (decrypted == NULL) {
        printf("Error: Memory allocation failed\n");
        free(raw_bytes);
        free(temp_buffer);
        return result;
    }
    
    for (int i = 0; i < bytes_length; i++) {
        decrypted[i] = raw_bytes[i] ^ best_key;
    }
    decrypted[bytes_length] = '\0';
    
    // save values to result struct
    result.decrypted = decrypted;
    result.score = best_score;
    result.key = (char)best_key;
    
    free(raw_bytes);
    free(temp_buffer);
    return result;
}

// DetectSingleCharXOR
void detect_char_xor(const char* filename) {
    struct scoring_data buffer_data;
    const int max_lines = 400;
    char line[max_lines];
    int line_num = 0;
    int best_score = 0;
    int best_line = 0;
    char best_key = 0;
    char* best_string = NULL;
    char* best_original_line = NULL;

    // open file
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // read each line
    while (fgets(line, max_lines, file) != NULL) { 
        line_num += 1;
        
        // Remove newline character if present (because fgets, reads with the newline char)
        size_t line_len = strlen(line);
        if (line_len > 0 && line[line_len-1] == '\n') { //null terminator is at line[line_len], therefore newline is at line[line_len-1]
            line[line_len-1] = '\0';
            line_len--; // account for the removal of 1 character by lowering the length by 1 character aswell
        }
        
        buffer_data = single_byte_xor(line);
        
        // If this score is better than our previous best
        if (buffer_data.score > best_score) {
            // Free previous best string if it exists
            if (best_string != NULL) {
                free(best_string);
            }
            
            // Free previous best original line if it exists
            if (best_original_line != NULL) {
                free(best_original_line);
            }
            
            // Save current best data
            best_string = buffer_data.decrypted;
            best_score = buffer_data.score;
            best_key = buffer_data.key;
            best_line = line_num;
            
            // Save a copy of the original line for printing later
            best_original_line = strdup(line);
        } else {
            // If we didn't keep this result, free its memory
            free(buffer_data.decrypted);
        }
    }

    // Output results
    printf("The line of the encrypted string is: %d\n", best_line);
    printf("String before decryption: %s\n", best_original_line);
    printf("Key: %c (0x%02X)\n", isprint(best_key) ? best_key : '?', best_key);
    printf("Score: %d\n", best_score);
    printf("Decrypted message: %s\n", best_string);

    // Clean up
    if (best_string != NULL) {
        free(best_string);
    }
    if (best_original_line != NULL) {
        free(best_original_line);
    }
    fclose(file);
}

// RepeatingKeyXOR
struct string_size repeating_key_xor(const char* plaintext, const char* key) {
    // Calculate lengths of input strings
    size_t key_length = strlen(key);
    size_t length = strlen(plaintext);

    // Allocate memory for output string (+1 for null-termination)
    char* output_str = (char*)malloc((length + 1) * sizeof(char));
    if (output_str == NULL) {
        fprintf(stderr, "RepeatingKeyXOR ERROR: Memory allocation failed\n");
        exit(1);
    }

    // Apply XOR operation with repeating key
    for (size_t i = 0; i < length; i++) {
        // XOR the current plaintext char with the corresponding key char
        output_str[i] = plaintext[i] ^ key[i % key_length];
    }

    // Null-terminate the string
    output_str[length] = '\0';

    // Create and return the struct
    struct string_size output_data;
    output_data.string = output_str;
    output_data.size = length;

    size_t hex_len = output_data.size * 2 + 1;
    char *hex_output = (char *)malloc(hex_len);
    
    if (hex_output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(output_data.string);
        exit(1);
    }
    
    // Convert to hex string
    hex_encode(output_data.string, output_data.size, hex_output);

    output_data.string = hex_output;
    return output_data; // The caller is responsible for freeing output_data.string
}

