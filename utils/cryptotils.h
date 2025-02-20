#ifndef CRYPTOTILS
#define CRYPTOTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "cryptotils.c"

uint8_t hex_char_to_value(char c);

uint8_t* hex_to_binary(char* hex_string);

char* binary_to_base64(uint8_t* binary_array, size_t binary_size, const char base64_chars[]);

char* xor_fixed(uint8_t* binary_buffer1, uint8_t* binary_buffer2, uint8_t binary_size1, uint8_t binary_size2);

#endif