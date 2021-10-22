# assignment1
SYSC 4001 - Assignment 1
Shuvaethy Neill 101143478

--------------------------------------------
DESCRIPTION
--------------------------------------------
This concurrent program consists of three processes that compute the determinant of a 3x3 matrix of integers and uses Linux shared memory to do so. 

*the variables used are to be stored in shared memory that is accessed by the processes.*


Matrix M is given by:

M = a b c

    d e f
    
    g h i

The parent process will fork three child processes P1, P2, P3. The computation of the detrminant is done by all the three child processes, where P1 computes a(ei-fh), P2 computes b(fg-di), and P3 computes c(dh-eg). 

It will print the following:
- determinant of the matrix
- largest integer of the matrix
- the time required to perform all the child process operations

The following two files are required:  
- DET.c
- DET.h

--------------------------------------------
INSTALLATION & SETUP
--------------------------------------------
