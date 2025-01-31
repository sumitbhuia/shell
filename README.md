# Custom Linux Shell in C++

## Overview
A high-efficiency custom shell written in C++ that seamlessly interfaces with the Linux kernel. It leverages system calls for precise command execution, optimizes process management with advanced forking, and ensures robust input parsing with dynamic memory handling.

## Features
- **Command Execution**: Supports execution of built-in and external Linux commands.
- **Process Management**: Optimized for performance with efficient forking and execution.
- **Input Parsing**: Handles user input robustly with dynamic memory management.
- **Minimalistic Interface**: Provides a clean and efficient CLI experience.

## Installation
### Prerequisites
- Linux-based OS
- C++ compiler (g++ recommended)

### Build Instructions
```sh
# Clone the repository
git clone https://github.com/sumitbhuia/shell.git
cd shell

# Run the shell
./my_shell
```

## Usage
- Enter any valid Linux command (e.g., `ls`, `pwd`, `cd`, `echo "Hello"`).
- Use `exit` to terminate the shell.


## Future Enhancements
- Redirection and piping support .
- Support for background processes (`&` operator).
- Enhanced error handling and debugging utilities.
- Custom environment variable support.


---
Developed by Sumit Bhuia


