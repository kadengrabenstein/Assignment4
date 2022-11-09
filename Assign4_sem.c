#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

pthread_t writers[10], readers[10];
pthread_t tid;
int numReaders = 0;
sem_t s_reader;
sem_t s_writer;

void *reader(void *param){
    sem_wait(&s_reader);
    numReaders++;
    if(numReaders == 1){
        sem_wait(&s_writer);
    }
    sem_post(&s_reader);
    printf("Reader %d starts reading\n", numReaders);
    sleep(1);
    sem_wait(&s_reader);
    numReaders--;
    if(numReaders == 0){
        sem_post(&s_writer);
    }
    sem_post(&s_reader);
    printf("Reader %d ends reading\n", numReaders + 1);
}

void *writer(void *param){
    sem_wait(&s_writer);
    printf("Writer has entered\n");
    if(numReaders == 0){
        sem_post(&s_writer);
    }else{
        sem_post(&s_reader);
    }
    printf("Writer has left\n");
}

int main(int argc, char *argv[]){
    sem_init(&s_reader,0,1);
    sem_init(&s_writer,0,1);
    for(int i=1; i<11; i++){
        atoi(argv[i]) == 0? pthread_create(&readers[i], NULL, reader, NULL) : pthread_create(&writers[i], NULL, writer, NULL);
    }
    return 0;
}