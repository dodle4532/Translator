# Rust-to-C Translator

This project is a simple translator (compiler) that converts a subset of Rust code into equivalent C code. It's implemented in C and designed to run on Linux systems.

## Features

The translator currently supports the following Rust features:

*   **Function Definitions:** Translates Rust function definitions (`fn`) to C function definitions.
*   **Basic Data Types:** Supports `u32`, `f32`, `bool`, `str` data types.
*   **Variables:** Translates variable declarations (`let mut`) to C variable declarations.
*   **Arithmetic Operations:** Handles basic arithmetic operations (+, -, \*, /).
*   **Conditional Statements:** Supports `if` statements.
*   **Return Statements:** Translates `return` statements.
*   **Loops:** Supports `for` and `while` loops.
*   **Print Statements:** Translates `println!` macro calls to C's `printf` function.
*   **Function Calls:** Able to do functions calls with parametrs

**Limitations:**

*   **String Literals:** Does not correctly handle string literals (the `str` type), according to true Rust.  Attempting to use string literals will result in a compiler error in Rust, but will work here.
*   **Example of using Strings:** 
    ```
    let str1: str = "123";
    let str2: str = "456";
    println!("'{str1}'+'{str2}' = {}\n", str1+str2);
    ```
*   **Subset of Rust:** Only a small subset of Rust is supported. More complex features of Rust are not yet implemented.
*   **Error Handling:**  Basic error handling is implemented, but may not cover all possible error scenarios.

## Getting Started

These instructions will guide you on how to build and run the translator on a Linux system.

### Prerequisites

*   **GCC:**  You need GCC (GNU Compiler Collection) installed on your system. Most Linux distributions come with GCC pre-installed. You can check if GCC is installed by running:

    ```bash
    gcc --version
    ```

    If it's not installed, you can usually install it using your distribution's package manager (e.g., `apt-get install gcc` on Debian/Ubuntu, `yum install gcc` on CentOS/RHEL).
*   **Make:**  You also need Make installed. You can check if Make is installed by running:

    ```bash
    make --version
    ```

    If it's not installed, use your package manager to install it (e.g., `apt-get install make`, `yum install make`).
*   **Git:** Git is required to clone the project.

### Building the Translator

1.  **Clone the Repository:**

    ```bash
    git clone <repository_url>  # Replace <repository_url> with the actual URL of your GitHub repository.
    cd <repository_directory>   # Replace <repository_directory> with the name of the cloned directory.
    ```

2.  **Compile the Translator:**

    Simply run the `make` command in the project directory:

    ```bash
    make
    ```

    This will compile all the C source files and create an executable file named `translator.out`.

### Running the Translator

1.  **Create a Rust Input File:**

    Create a text file (e.g., `test.txt`) containing the Rust code you want to translate.  Make sure the code adheres to the limitations mentioned above (no string literals!).  See the example input file in `test.txt` file.

2.  **Run the Translator:**

    Execute the `translator.out` program, providing the input file as a command-line argument:

    ```bash
    ./translator.out test.txt
    ```

    The translator will process the `test.txt` file and print the translated C code to the standard output (usually your terminal).
## More info

Check file 'Курсовая работа' to see more information about project.
