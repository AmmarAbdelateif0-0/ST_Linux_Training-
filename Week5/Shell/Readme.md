# MyShello

Welcome to the **MyShello** repository! This project is part of the **MyShello** shell implementation .
## Overview

This myshell is a command-line interpreter designed to handle various internal commands, execute external commands, and manage environment variables. It includes features such as process history and command type determination.

## Features

- *Internal Commands: Includes built-in commands such as **" mypwd, myecho, mycp, mymv, mycd, myenvir, exit, and help  "*.

- *External Commands*: Executes commands available in the system's PATH.

- *Command Type*: Determines if a command is internal, external, or unknown.

- *Environment Variables*: Prints the value of a specified environment variable if it exists.

## Built-in Commands List

Here is a list of the built-in commands currently supported:

1. **cd**: Change the current working directory.
2. **exit**: Terminate the shell session.
3. **echo**: Display a line of text or a variable's value.
4. **pwd**: Print the current working directory.
5. **help**: Display a list of available built-in commands and their usage.
6. **envir**: Display or modify environment variables.
7. **free**: display memory usage (RAM and swap) on Linux systems.
6. **cp**:  copy files or directories from one location to another.
7. **mv**:  used to move or rename files or directories.
6. **type**: determine how a command is interpreted (e.g., whether it is a built-in command, an alias, or an external program).
7. **uptime**: shows how long the system has been running, the number of users, and the system load averages.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC, Clang)
- Basic knowledge of shell scripting and C programming
- A Unix-like operating system (Linux, macOS, etc.) or Windows with WSL

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/AmmarAbdelateif0-0/MyShello.git

2. Navigate to the `MyShello` directory:
    ```bash
   cd MyShello
    ```
3. Compile the source code:
    ```bash
    make
    ```
4. Run the shell:
    ```bash
    ./myshello
    ```

### Usage
Once the shell is running, you can start using the built-in commands. For example:

* Change directory:
   ```bash
    cd /path/to/directory
    ```
* Print the current working directory::
    ```bash
    pwd
    ```
* Display a message:
    ```bash
    echo "Hello, World!"
    ```
* Exit the shell:
    ```bash
    exit
    ```
* shows how long the system has been running:
    ```bash
    uptime
    ```