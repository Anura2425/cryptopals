#ifndef CRYPTOTILS
#define CRYPTOTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "cryptotils.c"


int hex_to_int(char c);
size_t hex_decode(const char *hex_str, uint8_t **out);
char *base64_encode(const uint8_t *data, size_t input_length);
void hex_to_base64(const char *hex_string);

#endif