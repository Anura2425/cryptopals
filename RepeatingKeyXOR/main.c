#include <stdio.h>
#include "../utils/cryptotils.h"

int main(int argc, char *argv[]){
    const char* plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    const char* key = "ICE";
    
    struct string_size output_data = repeating_key_xor(plaintext, key, true);
    
    printf("Output  : %s\n", output_data.string);

    free(output_data.string);
    return 0;
}