#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include<unistd.h>

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
    printf("Reader %d starts reading\n", pthread_self());
    usleep(50);
    numReaders--;
    if(numReaders > 0){
        sem_wait(&s_reader);
    }
    printf("Reader %d ends reading\n", pthread_self());
    if(numReaders == 0){
        printf("Number of readers: %d\n", numReaders);
        sem_post(&s_writer);
    }
    sem_post(&s_reader);
    pthread_exit(0);
}

void *writer(void *param){
    printf("Writer is waiting\n");
    sem_wait(&s_writer);
    printf("Writer has entered\n");
    usleep(50);
    if(numReaders == 0){
        sem_post(&s_writer);
    }else{
        sem_post(&s_reader);
    }
    printf("Writer has left\n");
    pthread_exit(0);
}

int main(int argc, char *argv[]){
    sem_init(&s_reader,0,1);
    sem_init(&s_writer,0,1);
    for(int i=0; i<10; i++){
        printf("%d\n", atoi(argv[i+1]));
        atoi(argv[i+1]) == 0 ? pthread_create(&readers[i], NULL, reader, NULL) : pthread_create(&writers[i], NULL, writer, NULL);
    }
    return 0;
}