// Gavin McClure-Coleman
// Program that takes two equal-length buffers and produces their XOR combination
#include <stdio.h>
#include "../utils/cryptotils.h"

int main(int argc, char *argv[]){

    // test cases
    // case 1: buffers are of even length -> should output xord buffers in hexadecimal format
    char* buffer_a = "1c0111001f010100061a024b53535009181c";
    char* buffer_b = "686974207468652062756c6c277320657965";
    fixed_xor(buffer_a, buffer_b);
    // case 2: buffers are not of even length -> error message and exit code
    // printf("\n");
    // char* bad_buffer_a = "1c0111001f010100061a024b";
    // char* bad_buffer_b = "6869742074262";
    // fixed_xor(bad_buffer_a, bad_buffer_b);
    return 0;
}