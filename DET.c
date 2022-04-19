#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdbool.h>
#include "shared_mem.h"

#define MICRO_SEC_IN_SEC 1000000

int main(){

    int result = 0; 
    int largestNum = 0;
    struct timeval start, end;
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;
    int shmid;
    pid_t pid;

    shmid = shmget((key_t)8769, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    /*Make the shared memory accessibe to the program*/
    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Memory attached at %X\n", (int)shared_memory);

    shared_stuff = (struct shared_use_st *)shared_memory;
    
    /*Initialize int shared memory variables*/
    shared_stuff->count = 0;
    shared_stuff->busy = false;

    /*Initialize matrix M in shared memory*/
    int matrix[SIZE][SIZE] = {{20, 20, 50}, {10, 6, 70}, {40, 3, 2}};
    for(int m = 0; m < SIZE; m++){
        for(int n = 0; n < SIZE; n++){
            shared_stuff->M[m][n] = matrix[m][n];
        }
    }

    /*Fork 3 child processes*/
    for(int i = 0; i < SIZE; i++){
        if(i == 0){
            gettimeofday(&start,NULL);
        }
        pid = fork();
        switch(pid){

        //invalid
        case -1:
            perror("fork failed");
            exit(1);

        //child process
        case 0:
            //wait while another child process is doing its calculation and writing in shared memory 
            while(shared_stuff->busy == true) {}
            //if function is not busy then enter and do calculation
            if(shared_stuff->busy == false){
                //since this process will enter, it is now busy
                shared_stuff->busy == true;
                childCalculation(shared_stuff, i);
                //exited so no longer busy
                shared_stuff->busy == false;
            }
            //after last child process calculation is done, the time will stop
            if(shared_stuff->count == SIZE){
                gettimeofday(&end,NULL);
                printf("\nElapsedTime: %ldmicro sec\n", ((end.tv_sec * MICRO_SEC_IN_SEC + end.tv_usec)-(start.tv_sec * MICRO_SEC_IN_SEC + start.tv_usec)));
            }
            exit(0);

        default:
            break;
        }
    }

    /*Waiting for child processes, make sure they are terminanted*/
    wait(NULL);

    /*Comparing largest integers*/
    for(int j = 0; j < SIZE; j++){
        if(shared_stuff->L[j] > largestNum){
            largestNum = shared_stuff->L[j];
        }
    }
    printf("The largest integer in matrix M is %d\n", largestNum);

    /*Calculating the result determinant of matrix M*/
    result = shared_stuff->D[0] + shared_stuff->D[1] + shared_stuff->D[2];
    printf("The result determinant of matrix M is %d!\n", result);

    /*Detach and delete shared memory*/
    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}

/* Child process calculations for array D and largest integer*/
void childCalculation(struct shared_use_st *shared_stuff, int i){
    printf("Child Process: working with element %d of D\n", i+1);
    int num = 0;

    /*Calculating the largest integer in the respective row of matrix M and storing in shared memory*/
    for(int j = 0; j < SIZE; j++){
        if(shared_stuff->M[i][j] > num){
            num = shared_stuff->M[i][j];
        }
    }
    shared_stuff->L[i] = num;

    /*Calculation for Process 1*/
    if(i == 0){
        //computing a(ei-fh) and storing value in D[0] in shared memory
        shared_stuff->D[0] = shared_stuff->M[0][0] * ((shared_stuff->M[1][1])*(shared_stuff->M[2][2]) - (shared_stuff->M[1][2])*(shared_stuff->M[2][1]));
    }
    /*Calculation for Process 2*/
    else if (i == 1){
        //computing b(fg-di) and storing value in D[1] in shared memory
        shared_stuff->D[1] = shared_stuff->M[0][1] * ((shared_stuff->M[1][2])*(shared_stuff->M[2][0]) - (shared_stuff->M[1][0])*(shared_stuff->M[2][2]));
    }
    /*Calculation for Process 3*/
    else{
        //computing c(dh-eg) and storing value in D[2] in shared memory
        shared_stuff->D[2] = shared_stuff->M[0][2] * ((shared_stuff->M[1][0])*(shared_stuff->M[2][1]) - (shared_stuff->M[1][1])*(shared_stuff->M[2][0]));
    }
    
    //Keep track of how many processes have done their calculations
    shared_stuff->count += 1;
}
