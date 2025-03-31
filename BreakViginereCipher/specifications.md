<h1 style="text-align:center;">Function Specifications</h1>

<h3 style="text-align:center;">plaintext_to_binary()</h3>

---

<!-- Not sure if this in necessary or not, may just be able to directly use bitwise ops on ascii characters -->

### Purpose

    Converts a plaintext input to a string of binary

### Assumptions

    Expects an input of plaintext (ascii characters), assumes there is enough memory to create a new bitstring

### Inputs

    char* storing the text you wish to convert to binary

### Outputs

    char* storing the binary representation of the inputted string

### State Changes

    None

### Cases and Expected Behavior

    Take the input string as input, allocate memory for 8x the size of the initial string (8 bits per character), iterate through the characters, running bitwise & and a shifting the bits right as we go to convert each character to its bitewise representation. Then concatenate the current characters binary to the main binary string.

---

<h3 style="text-align:center;">compute_hamming_distance()</h3>

---

### Purpose

    Finds hamming distance (amount of differing bits) of two input buffers 

### Assumptions

    Two buffers exist and are correctly inputted into the function as such, the buffers can be in plaintext (uses plaintext_to_binary() to convert the inputted string to binary first, then continues with its functionality).
    or straight binary strings

### Inputs

    Two input buffers (char*) of either binary or plaintext

### Outputs

    An integer value representing the number of differing bits between the two inputted buffers

### State Changes

    None

### Cases/Expected Behaviors

    If the input is in plaintext, it will be converted to a string of binary first, then each bit of each string will be checked using the != operator to see if they are not the same value (1 vs 0 for example), if they are not the same then the count variable will be increased by 1. Continue until the end of the strings. Else if the input is in binary already, skip the conversion to binary step, and then the rest of the process is the same.

---

<h3 style="text-align:center;">read_file()</h3>

---

### Purpose

    Reads in text from a file and saves it to a char* for later

### Assumptions

    Assumes the file is a text file and that it is readable text


### Inputs

    A string holding the file_name

### Outputs

    A string holding the data from the file

### State Changes

    None

### Cases/Expected Behaviors

    If the file is readable, reads in the file line by line and saves it to a string, then returns that string


---

<h3 style="text-align:center;">b64_decode()</h3>

---

### Purpose

    Takes an input of Base64 Data and decodes it into a raw_bytes string to be used in other functions

### Assumptions
    
    Assumes the input has been Base64 encoded

### Inputs

    A char* holding the Base64 encoded data

### Outputs

    A char* holding the decoded data

### State Changes

    None

### Cases/Expected Behaviors

    If the input follows the assumptions, decode to plaintext from Base64, if not return an error
    


---

<h3 style="text-align:center;">break_viginere_cipher()</h3>

---

### Purpose

    Break the repeating key xor (viginere cipher) through a combination of steps(explained in cases and expected behavior)

### Assumptions

    Assumes the input is Ciphertext that has had the viginere cipher applied to it (also assumes the key length used is somewhere between 2 and 40 bytes in length)

### Inputs

    A char* holding a buffer of viginere encrypted data

### Outputs

    A struct holding a char* for the decoded message, a char* for the key, and an int for the key_size
    
### State Changes

    The internal hashmap will be constantly adding values for key_sizes and normalized edit distances, the hashmap will also be resorting to keep the structure of smallest to greatest normalized edit distance

### Cases/Expected Behaviors
 
   1) Create a Hashmap to store key and value pair for `key_size` (as key) and Normalized Edit Distance (as value),  
   2) Then loop through key sizes, taking the first `key_size` worth of bytes from the `ciphertext`, and the second `key_size` worth of bytes from the `ciphertext` and applying `compute_hamming_distance()` to the two blocks of bytes, then divide by the current `key_size` (this will give normalized edit distance), save that value to the hashmap along with its respective `key_size`. (keep hashmap sorted where the smallest edit distance is the first index and then the edit distances get larger as you go up in index), Lastly, save the `key_size` with the smallest normalized edit distance as the most likey `key_size` (we can call it something like `best_key_size`)
   3) Now, break the cipher text into blocks of size `key_size` (use a loop here), as we loop through make a block that stores all of the first bytes of each block of size key_size from the cipher text, a block that stores all of the second bytes, third bytes, and so on depending on the key size. 
   4) Solve each block as if it were a single byte XOR cipher because at this point all bytes that are in a block together will have been xor'd against the same character(byte), the highest score single byte key should be the key for that block.
   5) Almost done, now put the single byte keys together in order, this should be the correct key for the full viginere cypher
   6) Lastly, solve the whole cipher text as using the `RepeatingKeyXor()`, this should give you the final decrypted plaintext! Good Job!~
    

