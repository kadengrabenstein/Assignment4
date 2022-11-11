#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
sem_t s_reader,s_writer;
pthread_t tid;
pthread_t threads[10];
int numReaders = 0;

void *reader(void* param){
    sem_wait(&s_reader);
    numReaders++;
    if(numReaders==1)
        sem_wait(&s_writer);
    sem_post(&s_reader);
    printf("Reader %d starts reading\n",(int *)param);
    sleep(1);
    sem_wait(&s_reader);
    numReaders--;
    if(numReaders==0){
        sem_post(&s_writer);
    }
    sem_post(&s_reader);
    printf("Reader %d ends reading\n",(int *)param);
    return NULL;
}

void *writer(void* param){
    sem_wait(&s_writer);
    printf("Writer %d starts writing\n", (int*)param);
    sleep(1);
    sem_post(&s_writer);
    printf("Writer %d ends writing\n",(int *)param);
    return NULL;
}

int main(int argc, char *argv[]){
    sem_init(&s_reader,0,1);
    sem_init(&s_writer,0,1);
    for(int i=0; i<10; i++){
        atoi(argv[i+1]) == 0 ? pthread_create(&threads[i], NULL, reader, i) : pthread_create(&threads[i], NULL, writer, (i + 1));
    }
    for(int i=0;i<10;i++){
        pthread_join(threads[i],NULL);
    }
    return 0;
}