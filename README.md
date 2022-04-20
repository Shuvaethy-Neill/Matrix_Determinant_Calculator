# Matrix Determinant Calculator
Concurrent programming and shared memory

--------------------------------------------
DESCRIPTION
--------------------------------------------
This concurrent program consists of three processes that compute the determinant of a 3x3 matrix of integers and uses Linux shared memory to do so. 

Matrix M is given by:
```
M = a b c  
    d e f  
    g h i
```

The parent process will fork three child processes P1, P2, P3. The computation of the determinant is done by all the three child processes, where P1 computes a(ei-fh), P2 computes b(fg-di), and P3 computes c(dh-eg). The result of each child computation is summed to find the determinant of M. 

#### The program will print the following:
- the current process that is running
- the determinant of the matrix
- the largest integer of the matrix
- the time it took to perform all the child process operations

#### The following three files are included:  
- DET.c
- DET.h
- Makefile

INSTALLATION & SETUP
--------------------------------------------
You must have access to a Linux operating system in order to execute this program. 

If you do not have Linux installed on your machine, you can also create and use a virtual machine:
1. Download Oracle VirtualBox and create virtual machine
    - Download link: https://www.virtualbox.org/wiki/Download_Old_Builds_6_0
2. Download Fedora 30 ISO in the newly created virtual machine to be able to run Linux
    - Download link: https://archives.fedoraproject.org/pub/archive/fedora/linux/releases/30/Workstation/x86_64/iso/


USAGE
--------------------------------------------
Navigate to the directory in which these files are stored. You can do this using the cd command:

    cd directory_name
    
Ensure that you have both the DET.c source file and the supporting DET.h header file stored in the same directory. You can verify this by using the ls command and ensuring that the output displays 'DET.c', 'DET.h' and Makefile. 

Before executing the program to calculate the determinant of the matrix, you need to initialize the values by hardcoding them in the executable file on line 47.

To do so, open the DET.c file using the following command:
    
    vi DET.c  
    
The file will be opened with all of its content displayed. You can navigate your cursor through the code by using the up, down, left, and right arrow keys on your keyboard. To edit the values of the matrix M, navigate to the line where it is initialized, and press the 'i' key on you keyboard to enter insert mode. 

For example, if you wanted this matrix: 
```
M = 20 20 50 
    10  6 70  
    40  3  2  
```
then change line 47 to int M [SIZE][SIZE] = {{20, 20, 50}, {10, 6, 70}, {40, 3, 2}};

Once you are done editing the values,  press the 'esc' key on your keyboard to get out of insert mode. Then type the following to save and exit to go back to your directory in the terminal:

    :wq

Since changes have been made to the code, you will need to compile the file. Since the compile command is in the provided Makefile, you will just need to type the following in your terminal:

    make
    
This will create an executable file 'DET' that you can run (as per the command written in the Makefile).

To run the program after compilation enter the following:

    ./DET

The expected output resulting from the execution of the program is the current process that is running, the determinant of the matrix, the largest integer of the matrix, and the time it took to perform all the child process operations.

An example output for the input matrix above would be:
```
Memory attached at 8E5A3000
Child Process: working with element 1 of D
Child Process: working with element 2 of D
Child Process: working with element 3 of D

ElapsedTime: 174micro sec
The largest integer in matrix M is 70
The result determinant of matrix M is 41140!
```
*Note: the ElapsedTime will vary each time!*
