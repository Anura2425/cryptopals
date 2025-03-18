#include <stdio.h>  
#include "../utils/cryptotils.h"

int main(int argc, char* argv[]){
    //TODO: need a function that loads all lines from the file, applies the singlebytexor function to each line
    // returns the function that has a key
    char* filename = "buffers.txt";
    char key = detect_char_xor(filename);
    printf("The key is, %c", key);
    // Fix the other function from last challenge to actually return the key?
}