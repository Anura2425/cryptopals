
# **Function Specifications**

## 1. struct string_size repeating_key_xor(char* plaintext, char* key);

### Purpose:

Given a string of English-Plaintext, encrypt it using a repeating-key XOR cipher

### Assumptions:

* Use of another function 'hex_encode' to handle the encoding to hexadecimal after performing the XOR
* Assumes the input will be a correct string of English-Plaintext (readable ascii characters)

### Inputs:

1. char*: a string of English-Plaintext (i.e. "Hello, World!")
2. char*: a string for the key to be used in the cipher (i.e. "ICE")

### Outputs:

1. A struct (string_size) holding both:
   * char*: a string of encrypted text (in hexadecimal)
   * size_t: the size of the output string calculated based off of the size of the input string

### State Changes:

Plaintext is xord against the respective character of the key (we are xoring the raw byte representation of the characters). The resulting bytes/character is then saved into a new array called output_str. The output_str variable then has a null terminator concatenated  on the end to indicate the end of the output string.

### Expected Behaviors/Cases:

If the inputted string follows the assumptions, the function should apply the XOR operation with the specified repeating key, then return the raw_byte output along with the size of the string for later usage as needed.

If the inputted string fails to meet the requirements or something goes wrong during any memory allocation, print an error and exit the code.
