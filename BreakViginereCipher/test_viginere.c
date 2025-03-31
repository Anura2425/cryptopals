#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../utils/cryptotils.h"

int test_plaintext_to_binary(){
    // Setup
    char* string1 = "this is a test";
    char* string2 = "wokka wokka!!!";

    // Execution
    char* binary1 = plaintext_to_binary(string1);
    char* binary2 = plaintext_to_binary(string2);

    // Debug
    // printf("Binary1: %s \n", binary1);
    // printf("Binary2: %s \n", binary2);

    // Validation
    char* expected_binary1 = "0111010001101000011010010111001100100000011010010111001100100000011000010010000001110100011001010111001101110100";
    assert(strcmp(expected_binary1, binary1) == 0);
    char* expected_binary2 = "0111011101101111011010110110101101100001001000000111011101101111011010110110101101100001001000010010000100100001";
    assert(strcmp(expected_binary2, binary2) == 0);

    // Cleanup
    free(binary1);
    free(binary2);

    return 1;
}

int test_compute_hamming_distance(){
    // Setup
    char* text_buffer1 = "this is a test";
    char* text_buffer2 = "wokka wokka!!!";
    char* binary_buffer1 = "0111010001101000011010010111001100100000011010010111001100100000011000010010000001110100011001010111001101110100";
    char* binary_buffer2 = "0111011101101111011010110110101101100001001000000111011101101111011010110110101101100001001000010010000100100001";

    // Execution
    int text_hamming_distance = compute_hamming_distance(text_buffer1, text_buffer2);
    int binary_hamming_distance = compute_hamming_distance(binary_buffer1, binary_buffer2);

    // Debug
    // printf("text hamming distance: %d \n", text_hamming_distance);

    // Validation
    assert(text_hamming_distance == 37);
    assert(binary_hamming_distance == 37);

    // Cleanup
    return 1;
}

int test_base64_decode(){
    // Setup
    const char* base64_string = "SGVsbG8gV29ybGQh";
    size_t decoded_length;
    const char* expected_output = "Hello World!";

    // Execution
    unsigned char* decoded_string = base64_decode(base64_string, &decoded_length);

    // Debug
    // if (decoded_string != NULL) {
    //     printf("Decoded string: %s\n", decoded_string);
    //     free(decoded_string);
    // } else {
    //     printf("Decoding failed.\n");
    // }
    
    // Validation
    assert(strcmp((char*)decoded_string, expected_output) == 0);
    free(decoded_string);
    // Cleanup
    return 1;
}

int test_break_viginere_cipher(){
    // Setup
    const char* ciphertext = "";
    const char* expected_output = "";
    // Execution
    unsigned char* plaintext = "";
    // Debug

    // Validation
    assert(strcmp((char*)plaintext, expected_output) == 0);
    // Cleanup
    return 1;
}

int main(int argc, char** argv){
    
    printf("Plaintext to binary: %s \n", test_plaintext_to_binary() ? ("Passed! :D") : ("Failed. :("));
    printf("Compute hamming distance: %s \n", test_compute_hamming_distance() ? ("Passed! :D") : ("Failed. :("));
    printf("Decode Base64: %s \n", test_base64_decode() ? ("Passed! :D") : ("Failed. :("));
    printf("Break Viginere Cipher: %s \n", test_break_viginere_cipher() ? ("Passed! :D") : ("Failed. :("));

    return 0;
}