#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
sem_t s_reader,s_writer;  
pthread_t tid;
pthread_t threads[10];  //array that saves threads
int numReaders = 0;

void *reader(void* param){
    sem_wait(&s_reader);    //thread waits for the semaphore to be posted
    numReaders++;
    if(numReaders==1){
        sem_wait(&s_writer);    //writer must wait if there is a reader
    }
    sem_post(&s_reader);    //lets other readers in 
    printf("Reader %d starts reading\n",(int *)param);
    sleep(1);   //simulated reading
    sem_wait(&s_reader);    
    numReaders--;
    if(numReaders==0){      //allows writer in if there are no readers
        sem_post(&s_writer);
    }
    sem_post(&s_reader);
    printf("Reader %d ends reading\n",(int *)param);
    return NULL;
}

void *writer(void* param){
    sem_wait(&s_writer);    //thread waits for the semaphore to be posted
    printf("Writer %d starts writing\n", (int*)param);
    sleep(1);   //simulated writing
    sem_post(&s_writer);    
    printf("Writer %d ends writing\n",(int *)param);
    return NULL;
}

int main(int argc, char *argv[]){
    if(argc != 11){
        printf("Please enter 10 arguments from the command line\n");
        exit(0);
    }
    sem_init(&s_reader,0,1);    //reader semaphore initialization
    sem_init(&s_writer,0,1);    //writer semaphore initialization
    for(int i=0; i<10; i++){
        atoi(argv[i+1]) == 0 ? pthread_create(&threads[i], NULL, reader, (i + 1)) : pthread_create(&threads[i], NULL, writer, (i + 1)); //this creates a thread based off the input
        if (atoi(argv[i+1]) == 1) {
            pthread_join(threads[i],NULL);  //this join waits for writer threads
        } else if (i + 1 == 10) {
            pthread_join(threads[i],NULL);  //this join waits for the last thread
        }   
    }
    return 0;
}