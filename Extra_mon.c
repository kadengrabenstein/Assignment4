#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

pthread_t tid;
pthread_t threads[10];
int numReaders = 0;
int numWriters = 0;

sem_t s_reader, s_writer;
int numWaitingReaders = 0; // count for condition variable for readers
int numWaitingWriters = 0; // count for condition variable for writers

// declaring conditional variables
pthread_cond_t canRead = PTHREAD_COND_INITIALIZER;
pthread_cond_t canWrite = PTHREAD_COND_INITIALIZER;
// using mutex lock to ensure only one writer at a time with no other threads running
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 

// thread ends reading here
void *endRead(void *param) {
    printf("Reader %d ends reading\n",(int *)param);
    if (--numReaders == 0) {
        pthread_cond_signal(&canWrite);
    }
}

// thread starts reading here
void *startRead(void *param) {
    
    if (numWriters == 1 || numWaitingWriters > 0) {
        numWaitingReaders++;
        pthread_cond_wait(&canRead, &lock);
        numWaitingReaders--;
    }
    printf("Reader %d starts reading\n",(int *)param);
    numReaders++;
    sleep(1);
    pthread_cond_signal(&canRead);
    endRead((void *)param);
}

// thread ends writing here
void *endWrite(void *param) {
    numWriters = 0;
    pthread_mutex_unlock(&lock);
    printf("Writer %d ends writing\n",(int *)param);
    if (numWaitingReaders > 0) {
        pthread_cond_signal(&canRead);
    } else {
        pthread_cond_signal(&canWrite);
    }
}

// thread starts writing here
void *startWrite(void *param) {
    pthread_mutex_lock(&lock);
    if (numWriters == 1 || numReaders > 0) {
        numWaitingWriters++;
        pthread_cond_wait(&canWrite, &lock);
        numWaitingWriters--;
    }
    printf("Writer %d starts writing\n", (int*)param);
    sleep(1);
    numWriters = 1;
    endWrite((void *)param);
}

// main function to create and run threads
int main(int argc, char *argv[]){
    for(int i=0; i<10; i++) {
        atoi(argv[i+1]) == 0 ? pthread_create(&threads[i], NULL, startRead, (i + 1)) : pthread_create(&threads[i], NULL, startWrite, (i + 1));
        if (atoi(argv[i+1]) == 1) {
            pthread_join(threads[i],NULL);
        } else if (i + 1 == 10) {
            pthread_join(threads[i],NULL);
        }   
    }
    return 0;
}