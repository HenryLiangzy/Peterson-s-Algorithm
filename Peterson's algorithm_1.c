//
//  main.c
//  OS_ex2
//
//  Created by Henry Liang on 2017/11/6.
//  Copyright © 2017年 Henry Liang. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#define N 2  // Total number of threads (in addition to main thread).
#define M 100  // Number of loop iterations per thread.
int sum = 0;  // Data shared by all the threads.
int flag[N];
int turn = 0;
// The function executed by each thread.
void *runner(void *param) {
    int i = *(int *)param; // This thread’s ID number.
    
    
    
    
    
    int m;
    for(m = 0; m < M; m++) {
        
        /* Peterson's algorithm for thread 0 and 1 */
        flag[i] = 1;
        turn = N - 1 - i;
        while (flag[N - 1 - i] == 1 && turn == N - 1 - i) {
            //wait other theard finish and reset the flag
        }
        
        // Start of a Critical Section
        int s = sum;
        // Even threads increase s, odd threads decrease s.
        if(i % 2 == 0) {
            s++;
        } else {
            s--;
        }
        // Sleep a small random amount of time.  Do not remove this code.
        struct timespec delay;
        delay.tv_sec = 0;
        delay.tv_nsec = 100000000ULL * rand() / RAND_MAX;
        nanosleep(&delay, NULL);
        sum = s;
        // End of a Critical Section
        flag[i] = 0;
        printf("%c", 'A'+i); // Print this thread’s name.
        fflush(stdout);
    }
    
    
    
    
    return 0; // Thread dies.

}
int main(void) {
    pthread_t tid[N]; // Thread ID numbers.
    int param[N];     // One parameter for each thread.
    int i;
    // Create N threads.  Each thread executes the runner function with
    // i as argument.
    for(i = 0; i < N; i++) {
        param[i] = i;
        pthread_create(&tid[i], NULL, runner, &param[i]);
    }
    // Wait for N threads to finish.
    for(i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("\nResult is %d\n", sum);
    return 0; }
