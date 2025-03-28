#include <stdio.h>
#include <assert.h>
#include "../utils/cryptotils.h"

int test_plaintext_to_binary(){
    // Setup
    char* string1 = "this is a test";
    char* string2 = "wokka wokka!!!";

    // Execution
    char* binary1 = plaintext_to_binary(string1);
    char* binary2 = plaintext_to_binary(string2);

    // Debug
    // printf("Binary1: %s \n", binary1);
    // printf("Binary2: %s \n", binary2);

    // Validation
    char* expected_binary1 = "0111010001101000011010010111001100100000011010010111001100100000011000010010000001110100011001010111001101110100";
    assert(strcmp(expected_binary1, binary1) == 0);
    char* expected_binary2 = "0111011101101111011010110110101101100001001000000111011101101111011010110110101101100001001000010010000100100001";
    assert(strcmp(expected_binary2, binary2) == 0);

    // Cleanup
    free(binary1);
    free(binary2);

    return 1;
}

int main(int argc, char** argv){
    
    printf("Plaintext to binary: %s ", test_plaintext_to_binary() ? ("Passed! :D") : ("Failed. :("));
    return 0;
}