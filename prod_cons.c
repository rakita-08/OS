#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 5
#define TOTAL_ITEMS 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int producedCount = 0, consumedCount = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (producedCount >= TOTAL_ITEMS) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        int item = producedCount + 1;
        producedCount++;
        pthread_mutex_unlock(&mutex);

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (consumedCount >= TOTAL_ITEMS) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        consumedCount++;
        printf("Consumed: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("\nAll %d items produced and consumed. Exiting.\n", TOTAL_ITEMS);
    printf("Name:Rakita Rimal, Roll No:27, Lab No:2.4a");
    return 0;
}
