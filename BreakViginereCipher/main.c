#include <stdio.h>
#include "../utils/cryptotils.h"

int main(int argc, char **argv){
    
    // Step 1: Read file
    char* file_data = read_file("challenge6-data.txt");

    // Step 2: Decode Base64
    size_t decoded_length;
    char* ciphertext = base64_decode(file_data, &decoded_length);

    // Step 3: Break Viginere Cipher
    DataAndKey output_data = {NULL, NULL, 0};
    output_data = break_viginere_cipher(ciphertext, decoded_length);


    
    return 0;
}