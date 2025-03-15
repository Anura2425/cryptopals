#ifndef CRYPTOTILS
#define CRYPTOTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "cryptotils.c"

// General
int hex_to_int(char c);
char int_to_hex(int n);
int score_text(const char* text, size_t length);

// Hex to Base64
size_t hex_decode(const char* hex_str, uint8_t** out);
char* base64_encode(const uint8_t* data, size_t input_length);
void hex_to_base64(const char* hex_string);

// Fixed XOR
char* xor_binary(const uint8_t* buffer_a, const uint8_t* buffer_b, size_t input_length);
void fixed_xor(const char* buffer_a, const char* buffer_b);

// Single-bite xor cipher
void single_byte_xor(const char* hex_string);

#endif