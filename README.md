# ST_LinuxTraining

## program_1

### Write a C program consists of 2 C files, one file contains a function and one or more global variables (used in this function), and the second one contains the main function and uses the function defined in the first file.

#### To print this format
```
file1) text : number, data: number </br>
file2) text : number, data: number </br>
exec) text : number, data: number </br>
```
##### 1- Get executable file for each file
```
git -c file1.c
git -c file2.c
gir file1.c file2.c -o exec
```
##### 2- To know the size of each segment in the file
###### use " size " command
ex :
``` 
    size file1.o file2.o exec
```
output like :
```
   text    data     bss      dec     hex     filename
    149       4       4      157      9d     file1.o
    210       0       0      210      d2     file2.o
    781100    23232   23016  827348   c9fd4  exec

```

##### 3- then store the size you need in variable 

ex :
```
    testsize_file1=149
    datasize_file1=4
    ...etc
```

##### 3-then print these data

ex :
```
printf " file1) text = $texts_main , data = $datas_main\n file2) text = $texts_fun , data = $datas_fun \n exec) text =   $text_final , data = $datas_final \n"
```

output :
<img src ="https://github.com/user-attachments/assets/78d8a69e-49e1-4785-b4f5-7ff919b0876b">
