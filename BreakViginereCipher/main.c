#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/cryptotils.h"

int main(int argc, char **argv) {
    // Step 1: read the file data
    char* file_data = read_file("challenge6-data.txt");
    if (file_data == NULL) {
        fprintf(stderr, "Error reading file\n");
        exit(1);
    }
    
    // Step 1.5: Strip newlines
    strip_newlines(file_data);
    
    // Decode the base64 encoded file data
    size_t decoded_length;
    uint8_t* decoded_data = base64_decode(file_data, &decoded_length);
    
    if (decoded_data == NULL) {
        fprintf(stderr, "Error decoding base64 data\n");
        free(file_data);
        exit(1);
    }
    
    // Step 3: Break the viginere cipher
    DataAndKey output_data = break_viginere_cipher(decoded_data, decoded_length);
    if (output_data.data != NULL) {
        printf("Decrypted Message: \n");
        // Print character by character (did this because when using %s it was prematurely ending when encountering a null byte)
        for (size_t i = 0; i < decoded_length; i++) {
            printf("%c", output_data.data[i]);
        }
        printf("\n");
        
        printf("Best Key: %s\n", output_data.key);
        printf("Best Key_Size: %d\n", output_data.key_size);
        
        // Cleanup output_data
        free(output_data.data);
        free(output_data.key);
    }

    return 0;
}