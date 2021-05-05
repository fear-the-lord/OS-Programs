// Import all the necessary dependencies
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

sem_t mutex; // Indicates if there is a reader in the CS
sem_t db; // Indicates if the CS is free
pthread_t tid;
pthread_t writerthreads[100], readerthreads[100];
// Indicates the number of readers in the CS
int readercount = 0;

void *reader(void* param) {
    sem_wait(&mutex); // Indicates that a reader has entered the CS
    readercount++;
    if(readercount == 1)
        sem_wait(&db); // Indicates that the CS is now full
    sem_post(&mutex); // Allow other readers to enter
    printf("Reader %d is inside\n", readercount);
    sleep(3);
    readercount--;
    if(readercount == 0)
        sem_post(&db); // Indicates that the CS is free
    printf("Reader %d is leaving\n",readercount + 1);
    return NULL;
}

void *writer(void* param) {
    printf("Writer is trying to enter\n");
    sem_wait(&db); // If the CS is free writer will enter, else it will get stuck here
    printf("Writer has entered\n");
    sem_post(&db); // Make the CS free while leaving
    printf("Writer is leaving\n");
    return NULL;
}

int main() {
    int n, i;
    printf("Enter the number of readers:");
    scanf("%d", &n);
    printf("\n");
    // Initialize the semaphore variables x and y
    sem_init(&mutex, 0, 1);
    sem_init(&db, 0, 1);
    for(i = 0; i < n; i++) {
    	// Create the reader and writer threads
        pthread_create(&writerthreads[i], NULL, reader, NULL);
        pthread_create(&readerthreads[i], NULL, writer, NULL);
        // Run the threads
        pthread_join(writerthreads[i], NULL);
        pthread_join(readerthreads[i], NULL);
    }
}
