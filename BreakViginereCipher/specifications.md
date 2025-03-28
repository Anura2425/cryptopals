# **Function Specifications**

## 1. plaintext_to_binary() 
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

## 2. compute_hamming_distance()

### Purpose

    Finds hamming distance of input buffers 

### Assumptions

    Two buffers exist and are correctly inputted into the function as such, the buffers should be in binary.

### Inputs

    Two 

### Outputs

### State Changes

### Expected Outcomes/Cases


