#ifndef CRYPTOTILS
#define CRYPTOTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// STRUCTS

struct string_size{
    char* string;
    size_t size;
};

struct scoring_data{
    char* decrypted;
    int score;
    char key;
};

// General
int hex_to_int(char c);
char int_to_hex(int n);
int score_text(const char* text, size_t length);
void hex_encode(const char* input, size_t input_len, char* output);
char* plaintext_to_binary(const char* input);


// Hex to Base64 (ENCRYPT)
size_t hex_decode(const char* hex_str, uint8_t** out);
char* base64_encode(const uint8_t* data, size_t input_length);
void hex_to_base64(const char* hex_string);

// Fixed XOR (ENCRYPT)
char* xor_binary(const uint8_t* buffer_a, const uint8_t* buffer_b, size_t input_length);
void fixed_xor(const char* buffer_a, const char* buffer_b);

// Single-bite xor cipher (DECRYPT)
struct scoring_data single_byte_xor(const char* hex_string);

// Detect Single Character XOR (FIND and DECRYPT)
void detect_char_xor(const char* filename);

// Implement repeating-key XOR (ENCRYPT)
struct string_size repeating_key_xor(const char* plaintext, const char* key);

// Break Viginere Cipher
int compute_hamming_distance(const char* binary1, const char* binary2);

#endif