#ifndef CRYPTOTILS
#define CRYPTOTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

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

typedef struct {
    char* data;
    char* key;
    int key_size;
} DataAndKey;



// GENERAL FUNCTIONS:

int hex_to_int(char c);
char int_to_hex(int n);
int score_text(const char* text, size_t length);
void hex_encode(const char* input, size_t input_len, char* output);
bool is_binary_string(const char* input);
unsigned char* base64_decode(const char* input, size_t* output_length);
char* read_file(char* filename);
void strip_newlines(char* str);



// CHALLENGE SPECIFIC FUNCTIONS:

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

// Implement repeating-key XOR (ENCRYPT/decrypt)
struct string_size repeating_key_xor(const char* plaintext, const char* key, bool to_hex);

// Break Viginere Cipher (DECRYPT)
int compute_hamming_distance(const uint8_t* buffer1, const uint8_t* buffer2, size_t length);
int find_key_size(const uint8_t* ciphertext, size_t length);
char* find_key(int key_size, const uint8_t* ciphertext, size_t ciphertext_len);
DataAndKey break_viginere_cipher(uint8_t* ciphertext, size_t size);

#endif