#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../utils/cryptotils.h"

int main(){
    // main challenge test
    
    char* hex_string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    single_byte_xor(hex_string);

    // extra tests

    // Long text, tested with other ascii chars like periods
    char* hex_string2 = "14292A2A2F2861662F28662B3F6673687666312F322E662B3F663427213229366622293128663529662B3F662E272F346625272866242A293168";
    single_byte_xor(hex_string2);

    // no key test, (non printable character key)
    char* hex_string3 = "546869732069732061207465737420776974686F75742061206B6579";
    single_byte_xor(hex_string3);
}