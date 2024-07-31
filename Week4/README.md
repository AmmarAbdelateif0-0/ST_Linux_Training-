# **MyShell**

## **Overview**

This myshell is a command-line interpreter designed to handle various internal commands, execute external commands, and manage environment variables. It includes features such as process history and command type determination.

## **Features**

- *Internal Commands: Includes built-in commands such as **" mypwd, myecho, mycp, mymv, mycd, myenvir, exit, and help  "*.

- *External Commands*: Executes commands available in the system's PATH.

- *Command Type*: Determines if a command is internal, external, or unknown.

- *Environment Variables*: Prints the value of a specified environment variable if it exists.

## **Commands**

### - **Internal Commands**

- **mypwd**: Prints the current working directory.
  
  ```sh
    mypwd
  ```

- **myecho**: Prints the provided string to the standard output.
  
  ```sh
    myecho <string>
  ```

- **mycp**: Copies content from a source file to a destination file.
  
  ```sh
    mycp <source> <destination>
  ```  

- **mymv**: Moves or renames a file from source to destination.
  
 ```sh
    mymv <source> <destination>
  ```  

- **mycd**:  Changes the current working directory.
  
  ```sh
    mycd <directory>
  ```  

- **help** : Displays a list of available internalcommands and their descriptions.
  
  ```sh
    help
  ```  

- **exit** :   Exits the shell .
  
  ```sh
    exit
  ```

- **myenvir** : Prints the value of the specified environment variable if it exists.
  
  ```sh
    envir <variable>
  ```  

- **type**:   Determines if a command is internal, external, or unknown.
  
  ```sh
    type <command>
  ```    
------------------------
### - **External Commands**
External commands are any commands not built into the shell. The shell will attempt to execute these commands using the system's PATH

------------------------

## **Building and Running the Shell**

- **Clone the Repository** :     
  ```sh
    git clone <repository-url>
  ```    

- **Navigate to the Project Directory** :     
 ```sh
   cd <project-directory>
 ```    

- **Compile the Shell** : Use gcc or another compiler to compile the shell. For example:
  
  ```sh
    gcc  shell.c execution.c internal.c external.c -o my_shell
   ```  

- **Run the Shell** : 
  ```sh
    ./my_shell
   ```  

---------------------------------

## **Example Usage**
 
- **Start the Shell** : 
  ```sh
    ./my_shell
  ```  

- **Execute Internal Commands** : 
  ```sh
    my_shell> pwd
    /home/user

    my_shell> echo "Hello, World!"
    Hello, World!
  ```
     

- **Run External Commands** : 
  ```sh
    my_shell> ls -l
  ```   

- **Check Command Type** : 
  ```sh
    my_shell> type mypwd
    mypwd is an internal command

    my_shell> type ls
    ls is an external command
  ```   

- **Check Environment Variable** : 
  ```sh
    my_shell> envir PATH
    PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

  ```  
