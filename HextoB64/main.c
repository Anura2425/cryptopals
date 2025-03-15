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

int main() {
    // Challenge input
    const char *hex_string1 = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    hex_to_base64(hex_string1);

    // Other test cases
    //  const char *hex_string2 = "12345"; // 5 chars (odd, nums)
    // const char *hex_string3 = "123456"; // 6 chars (even, nums)
    // const char *hex_string4 = "abcde"; // 5 chars (odd, letters)
    // const char *hex_string5 = "abcdef"; // 6 chars (even, letters)
    // const char *hex_string6 = "1CE0F"; // 5 chars (odd, mix)
    // const char *hex_string7 = "ffe8b6"; // 6 chars (even, mix)
    
    // hex_to_base64(hex_string2);
    // hex_to_base64(hex_string3);
    // hex_to_base64(hex_string4);
    // hex_to_base64(hex_string5);
    // hex_to_base64(hex_string6);
    
    return 0;
}