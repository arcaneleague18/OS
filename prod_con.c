#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 3

int buffer[BUFFER_SIZE]; 
int in = 0;
int out = 0;
sem_t empty;
sem_t full;   
pthread_mutex_t mutex; 

void *producer(void *arg);
void *consumer(void *arg);

int main() {
    int choice;
    pthread_t prodThread, consThread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    printf("1. Press 1 for Producer\n");
    printf("2. Press 2 for Consumer\n");
    printf("3. Press 3 for Exit\n");

    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int fullval;
        sem_getvalue(&full,&fullval);
        if (choice == 1) {
            if(fullval==BUFFER_SIZE){
                printf("buffer full!!\n");
            }
            else{
                pthread_create(&prodThread, NULL, producer, NULL);
                pthread_join(prodThread, NULL);
            }
        } else if (choice == 2) {

            if (fullval == 0) {
                printf("Buffer is empty!\n");
            } else {
                pthread_create(&consThread, NULL, consumer, NULL);
                pthread_join(consThread, NULL);
            }
        } else if (choice == 3) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void *producer(void *arg) {
    static int item = 0; 

    sem_wait(&empty); 
    pthread_mutex_lock(&mutex); 

    item++; 
    buffer[in] = item;
    printf("Producer produces item %d\n", item);
    in = (in + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex); 
    sem_post(&full); 

    return NULL;
}

void *consumer(void *arg) {
    sem_wait(&full); 
    pthread_mutex_lock(&mutex); 

    int item = buffer[out];
    printf("Consumer consumes item %d\n", item);
    out = (out + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex); 
    sem_post(&empty); 

    return NULL;
}