#include <stdio.h>
#include "../utils/cryptotils.h"

int main(int argc, char **argv){
    
    char* test = "Hello";


    printf("%s ",  plaintext_to_binary(test));

    return 0;
}