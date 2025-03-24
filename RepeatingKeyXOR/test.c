#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/cryptotils.h"

int main(int argc, char *argv[]) {

    // 1) Setup
    char input[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    char key[] = "ICE";
    char* expected_output = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
    
    // Compute XOR result (raw bytes) and allocate enough space for output
    struct string_size result = repeating_key_xor(input, key);
    size_t hex_len = result.size * 2 + 1;
    char *hex_output = (char *)malloc(hex_len);
    
    hex_encode(result.string, result.size, hex_output);
    
    // Debugging: Print hex output for verification
    // printf("Expected: %s\n", expected_output);
    // printf("Output  : %s\n", hex_output);
    

    // 2) Test
    assert(strcmp(hex_output, expected_output) == 0);
    
    printf("Test Passed!\n");
    
    // 3) Cleanup
    free(result.string);
    free(hex_output);
    
    return 0;
}