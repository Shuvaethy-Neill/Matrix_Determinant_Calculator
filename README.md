# assignment1
SYSC 4001 - Assignment 1
Shuvaethy Neill 101143478

--------------------------------------------
DESCRIPTION
--------------------------------------------
This concurrent program consists of three processes that compute the determinant of a 3x3 matrix of integers and uses Linux shared memory to do so. 

Matrix M is given by:

M = a b c
    d e f
    g h i

The parent process will fork three child processes P1, P2, P3. The computation of the determinant is done by all the three child processes, where P1 computes a(ei-fh), P2 computes b(fg-di), and P3 computes c(dh-eg). The result of each child computation is summed to find the determinant of M. 

The program will print the following:
- determinant of the matrix
- largest integer of the matrix
- the time required to perform all the child process operations

The following two files are included:  
- DET.c
- DET.h

--------------------------------------------
INSTALLATION & SETUP
--------------------------------------------
You must have access to a Linux operating system in order to execute this program. 
If you do not have Linux installed on your machine, you can also create and use a virtual machine. 

Creating a virtual machine:
1. Download Oracle VirtualBox and create virtual machine
    - Download link: https://www.virtualbox.org/wiki/Download_Old_Builds_6_0
2. Download Fedora 30 ISO in the newly created virtual machine to be able to run Linux
    - Download link: https://archives.fedoraproject.org/pub/archive/fedora/linux/releases/30/Workstation/x86_64/iso/


If you are a Carleton University student, you can execute this program through the SCE lab computers. 

Accessing the lab computers:
1. Ensure that you know the login credentials to your SCE account (Note: the login credentials to your SCE account are different from your MC1 account)
2. Connect to the Carleton University VPN
3. Open the terminal of your personal laptop device
4. Type the following command: ssh -p 30003 your_username@machine_number.labs.sce.carleton.ca
        Ex. ssh -p 30003 shuvaethyneill@me3475-33.labs.sce.carleton.ca
5. Enter your SCE account password

You will now be connected to the lab computer. 

Navigate to the directory in which these files are stored (you can do this using the cd command).

    - Ex: cd directory_name
    
Ensure that you have both the DET.c source file and DET.h header file stored in the same directory.

To compile the program enter the following:
    gcc DET.c -o DET
    
To run the program after compilation enter the following:
    ./DET
    
