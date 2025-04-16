#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "../utils/cryptotils.h"

int test_compute_hamming_distance(){
    // Setup
    char* text_buffer1 = "this is a test";
    char* text_buffer2 = "wokka wokka!!!";
    char* binary_buffer1 = "0111010001101000011010010111001100100000011010010111001100100000011000010010000001110100011001010111001101110100";
    char* binary_buffer2 = "0111011101101111011010110110101101100001001000000111011101101111011010110110101101100001001000010010000100100001";


    // Execution
    int text_hamming_distance = compute_hamming_distance(text_buffer1, text_buffer2, 15);
    int binary_hamming_distance = compute_hamming_distance(binary_buffer1, binary_buffer2, 113);

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
    const char* base64_string = "QUJDMTIzVGVzdCBMZXRzIFRyeSB0aGlzJyBpbnB1dCBhbmQgc2VlIFdoYXQgImhhcHBlbnMi";
    size_t decoded_length;
    const char* expected_output = "ABC123Test Lets Try this' input and see What \"happens\"";

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

int test_find_key_size() {
    // Setup
    const char* plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    const char* key = "ICE";
    struct string_size data = repeating_key_xor((unsigned char*)plaintext, (unsigned char*)key, false);
    int size = strlen(data.string);

    if (data.string == NULL) {
        fprintf(stderr, "Memory allocation failed for ciphertext.\n");
        return 0;
    }

    char* ciphertext = data.string;

    // Execution
    int key_size = find_key_size(ciphertext, size);

    // Validation
    assert(key_size == 3);

    // Cleanup
    free(ciphertext);

    return 1;
}

int test_break_viginere_cipher() {
    // Setup
    const char* plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    const char* key = "ICE";
    size_t plaintext_len = strlen(plaintext);
    
    struct string_size encrypted = repeating_key_xor(plaintext, key, false);
    if (encrypted.string == NULL) {
        fprintf(stderr, "Error encrypting plaintext\n");
        return 0;
    }
    
    // Execution
    DataAndKey decrypted_data = break_viginere_cipher((uint8_t*)encrypted.string, encrypted.size);
    
    // Validation
    int success = (decrypted_data.data != NULL && decrypted_data.key != NULL && strcmp(decrypted_data.key, key) == 0 &&strcmp(decrypted_data.data, plaintext) == 0);
    
    // Cleanup
    free(encrypted.string);
    if (decrypted_data.data){
        free(decrypted_data.data);
    } 
    if (decrypted_data.key) {
        free(decrypted_data.key);
    }
    
    return success;
}


int main(int argc, char** argv){
    
    printf("Compute hamming distance: %s \n", test_compute_hamming_distance() ? ("Passed! :D") : ("Failed. :("));
    printf("Decode Base64: %s \n", test_base64_decode() ? ("Passed! :D") : ("Failed. :("));
    printf("Find Key Size: %s \n", test_find_key_size() ? ("Passed! :D"): ("Failed. :("));
    printf("Break Viginere Cipher: %s \n", test_break_viginere_cipher() ? ("Passed! :D") : ("Failed. :("));

    return 0;
}