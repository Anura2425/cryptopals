<h1 style="text-align:center;">Function Specifications</h1>

<h3 style="text-align:center;">compute_hamming_distance()</h3>

---

### Purpose

    Finds hamming distance (amount of differing bits) of two input buffers 

### Assumptions

    Two buffers exist and are correctly inputted into the function as such, the buffers can be in plaintext or binary

### Inputs

    Two input buffers (const uint8_t*) of either binary aswell as the length of the buffers (as size_t)

### Outputs

    An integer value representing the number of differing bits between the two inputted buffers

### State Changes

    None

### Cases/Expected Behaviors

    Checks that the input buffers aren't NULL, if they are return -1 (error). If they arent move on and loop through the length of the buffers, XORing the bytes and counting the differing bits as we go.

---

<h3 style="text-align:center;">read_file()</h3>

---

### Purpose

    Reads in text from a file and saves it to a char* (string)

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

<h3 style="text-align:center;">find_key_size()</h3>

---

### Purpose

    Find the key size used on a specific ciphertext

### Assumptions

    The string of ciphertext has had the viginere cipher applied to it (basically there is a key that was used for this function to find the size of)

### Inputs

    A string (const uint8_t*) of ciphertext, and length of the ciphertext length (size_t)

### Outputs

    An Integer (int) representing the length of the key
 
### State Changes

    None

### Cases/Expected Behaviors

    Loop through the key sizes 2 - 40. Then we loop to divide the ciphertext in blocks. Then we loop through the blocks to calculate the hamming distance. The smallest distance is the best size. Thus, it is returned as the key_size.


---

<h3 style="text-align:center;">find_key()</h3>

---
### Purpose

    Find the key used on a specific ciphertext

### Assumptions

    The string of ciphertext has had the viginere cipher applied to it (basically there is a key that was used for this function to find the size of) and we know the keys length (used find_key_size() prior)

### Inputs

    An integer (int) representing the key_size, the ciphertext (const uint8_t*), the length of the ciphertext as size_t

### Outputs

    A char* that is the key used on the ciphertext
 
### State Changes

    None

### Cases/Expected Behaviors

    First allocate memory for the different blocks of ciphertext we will be working with.   
    Then break the cipher text into blocks of key_size length (this is because if the key_size we found was indeed used on the original text to create this cipher text, it would have repeating xor'd against the text, making groups 'blocks' in our case that  are the length of the key).
    Now allocate memory for the transposed blocks, and then transpose the blocks (This is  because we are going to be rearranging the bytes in away that the bytes that were xor'd against the same character will be grouped together).  
    Then we solve each of these blocks as if they were single XOR ciphered (since the groups should have all been xord against the same character within their respective group at this point), and this will give us the most likely byte for each block in the key.  
    Put these new bytes (characters) in order and you will get the key!  
    If at anypoint memory allocation or one of these proccesses fails, exit the code by returning  NULL.  
    If it doesn't fail, youve done it! Return the key and get ready to decipher the text 😼!

---

<h3 style="text-align:center;">break_viginere_cipher()</h3>

---

### Purpose

    Break the repeating key xor (viginere cipher) through a combination of steps(explained in cases and expected behavior)

### Assumptions

    Assumes the input is Ciphertext that has had the viginere cipher applied to it (also assumes the key length used is somewhere between 2 and 40 bytes in length)

### Inputs

    A char* holding a buffer of viginere encrypted data, and the size of the ciphertext (size_t)

### Outputs

    A struct holding a char* for the decoded message, a char* for the key, and an int for the key_size
    
### State Changes

    The internal hashmap will be constantly adding values for key_sizes and normalized edit distances, the hashmap will also be resorting to keep the structure of smallest to greatest normalized edit distance

### Cases/Expected Behaviors
 
1) First find the key length using the `find_key_size()` function,  
2) Then find the key itself by using the `find_key()` function,
3) Lastly, solve the whole cipher text as using the `RepeatingKeyXor()`, this should give you the final decrypted plaintext! Good Job!~
