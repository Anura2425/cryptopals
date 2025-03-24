#include <stdio.h>
#include "../utils/cryptotils.h"

int main(int argc, char *argv[]){
    const char* plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    const char* key = "ICE";
    
    struct string_size result = repeating_key_xor(plaintext, key);
    
    size_t hex_len = result.size * 2 + 1;
    char *hex_output = (char *)malloc(hex_len);
    
    if (hex_output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(result.string);
        return 1;
    }
    
    // Convert to hex string
    hex_encode(result.string, result.size, hex_output);
    printf("Output  : %s\n", hex_output);

    // free the dynamically allocated memory
    free(result.string);
    return 0;
}