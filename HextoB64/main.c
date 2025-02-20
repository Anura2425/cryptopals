/*
Hex to Base64
Programmer: Gavin McClure-Coleman
Contents: Program to convert Hexadecimal to Base64
*/ 
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../utils/cryptotils.h"

int main(int argc, char *argv[])  
{   
    // TODO: take user input instead maybe?
    // TYPE HEXADECIMAL STRING TO CONVERT HERE: Must be even length to work properly as of right now.
    char *hex_string = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    uint8_t* binary_array = hex_to_binary(hex_string);
    size_t hex_length = strlen(hex_string);
    // checks for the case that the hex string starts with 0x or not, gives the correct size either way
    size_t binary_size = (hex_length - (hex_string[1] == 'x' || hex_string[1] == 'X' ? 2 : 0)) * 4; 

    char* b64_string = binary_to_base64(binary_array, binary_size, base64_chars);

    printf("Hexadecimal String: ");
    printf("%s\n", hex_string);
    printf("\nBase64 Encoded String: ");
    printf("%s\n", b64_string);
    printf("\n");

    free(binary_array);
    free(b64_string);
    
    return 0;
}