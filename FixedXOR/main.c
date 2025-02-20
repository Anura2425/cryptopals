// Gavin McClure-Coleman
// Program that takes two equal-length buffers and produces their XOR combination
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../utils/cryptotils.h"

int main(int argc, char *argv[]){

    char* buffer1 = "1c0111001f010100061a024b53535009181c";
    char* buffer2 = "686974207468652062756c6c277320657965";
    uint8_t* binary_buffer1 = hex_to_binary(buffer1);
    uint8_t* binary_buffer2 = hex_to_binary(buffer2);
    size_t buffer_length1 = strlen(buffer1);
    size_t buffer_length2 = strlen(buffer2);
    // checks for the case that the hex string starts with 0x or not, gives the correct size either way
    size_t binary_size1 = (buffer_length1 - (buffer1[1] == 'x' || buffer1[1] == 'X' ? 2 : 0)) * 4; 
    size_t binary_size2 = (buffer_length2 - (buffer2[1] == 'x' || buffer2[1] == 'X' ? 2 : 0)) * 4; 

    char* output_buffer = xor_fixed(binary_buffer1, binary_buffer2, binary_size1, binary_size2);


    return 0;
}