#include <stdio.h>
#include "../utils/cryptotils.h"

int main(int argc, char *argv[]){
    const char* plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    const char* key = "ICE";
    
    struct string_size result = repeating_key_xor(plaintext, key);
    
    printf("Output  : %s\n", result.string);

    // free the dynamically allocated memory
    free(result.string);
    return 0;
}