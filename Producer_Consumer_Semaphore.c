// Import the necessary dependencies
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

// Bound the Buffer Size
#define Buffer_Limit 10
 
int Buffer_Index_Value = 0;
int count_consumer = 0; 
int count_producer = 0;
char item = '@';
char *Buffer_Queue;
 
pthread_mutex_t mutex_variable = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Buffer_Queue_Not_Full = PTHREAD_COND_INITIALIZER;
pthread_cond_t Buffer_Queue_Not_Empty = PTHREAD_COND_INITIALIZER;
 
void *Consumer() {
      while(count_consumer <= 10) {
      	// Once the control comes here, the mutex will be locked
        pthread_mutex_lock(&mutex_variable);
        // Check if the buffer is empty
        if(Buffer_Index_Value == -1) {     
            printf("Please wait until the buffer has some items!\n");
            pthread_cond_wait(&Buffer_Queue_Not_Empty, &mutex_variable);
        }             
		// If the buffer is not empty, consumer consumes an item from the buffer   
        printf("Consumer consumes item %c from position %d \n", Buffer_Queue[Buffer_Index_Value], Buffer_Index_Value--);        
        // Unlock the mutex once the Consumer Consumes the item from the buffer
        pthread_mutex_unlock(&mutex_variable); 
		// Signal that an item has been consumes from the buffer       
        pthread_cond_signal(&Buffer_Queue_Not_Full);   
		count_consumer++;  
		printf("--------------------------------------------------------------------------------------------------------------\n");
	}
}
 
void *Producer() {    
      while(count_producer <= 10) { 
      	// Once the control comes here, the mutex will be locked
        pthread_mutex_lock(&mutex_variable);
        // Check if the Buffer Size is full
        if(Buffer_Index_Value == Buffer_Limit)
        {                        
            printf("Please wait until the buffer has some space!\n");
            pthread_cond_wait(&Buffer_Queue_Not_Full, &mutex_variable);
        }                        
        // If buffer is not full, produce an item in the buffer
        item = item + 1;
        Buffer_Queue[Buffer_Index_Value++] = item;
        printf("Producer has produced item %c at location %d\n", Buffer_Queue[Buffer_Index_Value - 1], Buffer_Index_Value);
        // Unlock the mutex once the Producer produces an item into the buffer
        pthread_mutex_unlock(&mutex_variable);
        // Signal that the buffer has some items
        pthread_cond_signal(&Buffer_Queue_Not_Empty);   
		count_producer++;  
		printf("--------------------------------------------------------------------------------------------------------------\n");   
    }    
}
 
int main() {    
    pthread_t producer_thread_id, consumer_thread_id;
    Buffer_Queue = (char *) malloc(sizeof(char) * Buffer_Limit);    
	// Create the Producer and the Consumer Thread        
    int err1 = pthread_create(&producer_thread_id, NULL, Producer, NULL);
    int err2 = pthread_create(&consumer_thread_id, NULL, Consumer, NULL);
    if(err1 & err2) {
    	printf("Thread Creation Unsuccessful!");
      	exit(1);
	} else {
	  	// If the threads are created successfully, then wait for them to terminate 
	  	pthread_join(producer_thread_id, NULL);
      	pthread_join(consumer_thread_id, NULL);
	}
	printf("No:of items remaining in the buffer = %d", count_producer - count_consumer);
    return 0;
}
