// Import the necessary dependencies
#include <stdio.h>
#include <stdlib.h>
 
int temp = 0, overflow = 0, mutex = 1, underflow = 10;
 
int wait_protocol(int counter) {
    return (--counter);
}
 
int signal_protocol(int counter){
    return(++counter);
}
 
void producer() {
	// Make the mutex 0, in so that the consumer process doesnot enter the Critical Section
    mutex = wait_protocol(mutex);
    // Add an item into the buffer
    overflow = signal_protocol(overflow);
    // Reduce size of the buffer by 1
    underflow = wait_protocol(underflow);
    temp++;
    printf("\nProducer produces element %d\n", temp);
    printf("------------------------------------------\n");
    // Free the Critical Section
    mutex = signal_protocol(mutex);
}
 
void consumer() {
	// Make the mutex 0, in so that the consumer process doesnot enter the Critical Section
    mutex = wait_protocol(mutex);
    // Reduce size of the buffer by 1
    overflow = wait_protocol(overflow);
    // Increase free space of the buffer by 1
    underflow = signal_protocol(underflow);
    printf("\nConsumer consumes element %d\n", temp);
    printf("------------------------------------------\n");
    temp--;
    // Free the Critical Section
    mutex = signal_protocol(mutex);
}
 
int main() {
      int choice;
      int count = 0;
      printf("\n1.Producer\t");
      printf("2. Consumer\t");
      printf("3. Quit\t");
      while(count  != 10) {
            printf("\nEnter your choice:\t");
            scanf("%d", &choice);
            switch(choice) {
                case 1: if((mutex == 1) && (underflow != 0)) 
                    producer();
                    else
                    	printf("Please wait for a free space in the buffer!\n");
                    break;
                          
                case 2: if((mutex == 1) && (overflow != 0)) 
                    consumer();
                	else
                        printf("Please wait for an item to be produced in the buffer!\n");
                    break;
                          
                case 3: exit(0);
                        break;
            }
        printf("No: of elements in the buffer = %d", temp);
        count++;
    }
    return 0;
}
