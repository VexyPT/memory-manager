# Memory Management Simulator 🧠

## Overview 📖

Welcome to the **Memory Management Simulator**! This C program demonstrates key concepts of dynamic memory allocation and deallocation. It allows users to allocate, free, and track memory blocks, while also checking for memory leaks.

### Key Features ✨

- **Allocate Memory**: Dynamically allocate memory blocks with a specified size.
- **Free Memory**: Frees previously allocated memory blocks by their index.
- **Display Memory Status**: View the current memory allocation status, including active blocks.
- **Memory Leak Detection**: Identifies unfreed memory blocks upon program exit.
- **User-Friendly Interface**: Ensures smooth user interaction with input validation and error handling.

### Requirements 🛠️

- **C Compiler**: GCC or any C compiler.
- **Operating System**: Works on Linux, macOS, or any POSIX-compliant OS. Windows users can use WSL or MinGW.

### Compilation and Setup 🔧

To compile the project, open your terminal and run the following commands:

1. Clone the repository:
    ```bash
   git clone https://github.com/yvexypt/memory-manager.git
   cd memory-manager
   ```
2. Compile the code:
   ```bash
   gcc -o memory_manager memory_manager.c
   ```
    If you are using **CMake**, follow these steps:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

# Running the Program 🚀
Once compiled, you can run the program with:
   ```bash
   ./memory-manager
   ```
Upon running the program, you will be presented with the following menu:
1. **Allocate Memory:** Allocate a new memory block of a given size.
2. **Free Memory:** Free a previously allocated memory block by selecting its index.
3. **Display Memory Status:** View the total memory allocated and details of each active memory block.
4. **Exit:** Exit the program and check for any memory leaks.

# Example Usage 📊

   ```bash
   --- Memory Management Simulator ---
1. Allocate memory
2. Free memory
3. Display memory status
4. Exit
Enter your choice: 1
Enter the size of memory block to allocate (in bytes): 256
Memory allocated: Address=0x7f8fbd3a7420, Size=256 bytes

--- Memory Management Simulator ---
1. Allocate memory
2. Free memory
3. Display memory status
4. Exit
Enter your choice: 3

--- Memory Status ---
Total allocated memory: 256 bytes
Number of active blocks: 1
Block 0 -> Address: 0x7f8fbd3a7420, Size: 256 bytes
---------------------
   ```

# Memory Management Concept 🧑‍💻
This program simulates memory allocation in C using `malloc` for allocating and `free` for deallocating memory. The memory blocks are tracked in an array of `MemoryBlock` structs, each containing the block's address and size.

# Memory Leak Detection 🔍
The program performs a check for any memory leaks upon exiting. If there are memory blocks that haven't been freed, they will be reported.

# License 📜
This project is licensed under the MIT License. For more details, check the LICENSE file.

# Contributions 🤝
Feel free to fork this repository and submit pull requests for improvements, bug fixes, or new features. For reporting issues or asking questions, open an issue on GitHub.