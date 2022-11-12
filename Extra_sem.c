#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include <sys/stat.h>
#include <fcntl.h>

#define WRITER "/writer"
#define READER "/reader"
pthread_t tid;
pthread_t threads[10];
int numReaders = 0;
sem_t *s_reader;
sem_t *s_writer;

void reader(int param){
    sem_wait(&s_reader);
    numReaders++;
    if(numReaders==1){
        sem_wait(&s_writer);
    }
    sem_post(&s_reader);
    printf("Reader %d starts reading\n",param);
    sleep(1);
    sem_wait(&s_reader);
    numReaders--;
    if(numReaders==0){
        sem_post(&s_writer);
    }
    sem_post(&s_reader);
    printf("Reader %d ends reading\n",param);
    return;
}

void writer(param){
    sem_wait(&s_writer);
    printf("Writer %d starts writing\n", param);
    sleep(1);
    sem_post(&s_writer);
    printf("Writer %d ends writing\n",param);
    return;
}

int main(int argc, char *argv[]){
    s_reader = sem_open(READER, O_CREAT, 0644, 1);
    s_writer = sem_open(WRITER, O_CREAT, 0644, 1);
    for(int i=0; i<10; i++){
        if(atoi(argv[i+1]) == 0){
            if(fork() == 0){
                reader(i+1);
            }else{
                break;
            }
        }else{
            if(fork() == 0){
                writer(i+1);
            }else{
                break;
            }
        }
    }
    return 0;
}