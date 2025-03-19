#include <stdio.h>  
#include <ctype.h>
#include "../utils/cryptotils.h"

int main(int argc, char *argv[]){
    // main challenge test
    struct scoring_data hex_data1;
    char* hex_string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    hex_data1 = single_byte_xor(hex_string);
    printf("Key: %c (0x%02X)\n", isprint(hex_data1.key) ? hex_data1.key : '?', hex_data1.key);
    printf("Score: %d\n", hex_data1.score);
    printf("Decrypted message: %s\n", hex_data1.decrypted);
}