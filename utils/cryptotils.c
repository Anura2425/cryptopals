
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// base64 character set
const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

uint8_t hex_char_to_value(char c){
    /*
    Converts individual hexadecimal character to its integer value
    For example:
    F => 15
    */ 
    if (c >= '0'  && c <= '9') {
        return c - '0';
    }
    else if (c >= 'a' && c <= 'f'){
        return c - 'a' + 10;
    }
    else if (c >= 'A' && c <= 'F'){
        return c - 'A' + 10;
    } else {
        printf("Invalid Hexadecimal Character:\n");
        printf("%c\n", c);
        exit(EXIT_FAILURE);
    }
    return 0;
}

uint8_t* hex_to_binary(char* hex_string){
    /* 
    Converts hexadecimal character string to decimal array
    
    Works for both hexstrings that start with 0x and without

    utilizes the hex_char_to_value() function to convert
    individual hex characters
    */ 
    int size = strlen(hex_string);
    int* hex_value_array;
    hex_value_array = (int*) malloc(size * sizeof(int));
    if (hex_value_array == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    if (hex_string[1] == 'x' || hex_string[1] == 'X'){
        for(int i = 2; i < size; i++){
            hex_value_array[i - 2] = hex_char_to_value(hex_string[i]);
        }
    } else {
        for(int i = 0; i < size; i++){
            hex_value_array[i] = hex_char_to_value(hex_string[i]);
        }
    }

    // Converts decimal array to binary conversion
    int binary_size = size * 4; // use 4 here b/c each hex digit is represented by 4 binary digits
    uint8_t* binary_array;
    binary_array = (uint8_t*) malloc(binary_size * sizeof(uint8_t));
    if (binary_array == NULL) {
        return NULL;
    }
    // Convert each hex value to its binary representation
    for (int i = 0; i < size; i++){
        // Each hex digit represents 4 binary digits so use 4 again
        for (int j = 0; j < 4; j++){
            // Shift the hex value right by (3-j) and mask with 1 to get the j-th binary digit
            binary_array[i*4 + j] = (hex_value_array[i] >> (3-j)) & 1;
        }
    }
    
    // can remove later just for testing prints of binary
    // printf("\n");
    // for (int i = 0; i < binary_size; i++){ 
    //     printf("%d", binary_array[i]);
    // }

    free(hex_value_array);
    return binary_array;
}

char* binary_to_base64(uint8_t* binary_array, size_t binary_size, const char base64_chars[]){
    /*
    Converts binary array to base64 characters
    Make sure to free after usage
    */ 
    size_t output_size = ((binary_size + 5) / 6 + 3) / 4 * 4;
    char* b64_string = (char*) malloc(output_size + 1);
    if (b64_string == NULL){
        return NULL;
    }

    uint32_t temp_buffer;
    size_t i, j;
    char* b64_output_pointer = b64_string;

    for (i = 0; i < binary_size; i += 6) { // Read 6-bit chunks
        temp_buffer = 0;
        for (j = 0; j < 6 && (i + j) < binary_size; j++) {
            temp_buffer |= binary_array[i + j] << (5 - j); 
        }
        // Encode to Base64
        *b64_output_pointer++ = base64_chars[temp_buffer & 0x3F]; // 0x3F = 00111111 - use to mask only 6 bits at a time
    }
    // Pad output to be a multiple of 4
    while ((b64_output_pointer - b64_string) % 4 != 0) {
        *b64_output_pointer++ = '=';
    }

    *b64_output_pointer = '\0'; // Null-terminate (gets rid of garbage value at end of b64 string)
    return b64_string;
}

char* xor_fixed(uint8_t* binary_buffer1, uint8_t* binary_buffer2, uint8_t binary_size1, uint8_t binary_size2){
    if(binary_size1 == binary_size2){
        // TODO: xor_fixed code
    } else {
        printf("ERROR: Buffers must be same length.");
        exit(EXIT_FAILURE);
    }
    return "happy";
}