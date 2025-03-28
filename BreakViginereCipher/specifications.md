<h1 style="text-align:center;">Function Specifications</h3>

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

### Assumptions

### Inputs

### Outputs

### State Changes

### Cases/Expected Behaviors

---

<h3 style="text-align:center;">b64_decode()</h3>

---

### Purpose

### Assumptions

### Inputs

### Outputs

### State Changes

### Cases/Expected Behaviors

---

<h3 style="text-align:center;">break_viginere_cipher()</h3>

---

### Purpose

### Assumptions

### Inputs

A char* holding a buffer of encrypted data

### Outputs

A struct holding a char* for the decoded message, and a char* for the key

### State Changes

### Cases/Expected Behaviors

