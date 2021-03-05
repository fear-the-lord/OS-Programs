#include<stdio.h>

// Function to swap two numbers
void swap(int a, int b) {
	int temp; 
	temp = a; 
	a = b; 
	b = temp;
}

// Function to sort based on arrival time
void sort(int n, int process[], int arrival_time[], int burst_time[]) {
	int i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n - i - 1; j++) {
			if(arrival_time[j] >= arrival_time[j + 1]) {
				swap(arrival_time[j], arrival_time[j + 1]);
				swap(burst_time[j], burst_time[j + 1]);
				swap(process[j], process[j + 1]);
			}
		}
	}
}

// Implementation of First Come First Serve Scheduling 
void first_come_first_serve(int n, int process[], int arrival_time[], int burst_time[]) {
	int completion_time[n], turn_around_time[n], waiting_time[n];
	int total_turn_around_time = 0, total_waiting_time = 0;
	sort(n, process, arrival_time, burst_time);
	int i, start_time = 0;
	for(i = 0; i < n; i++) {
		// If start time is less than arrival time, then wait till the process arrives
		if(start_time < arrival_time[i]) 
			start_time = start_time + (arrival_time[i] - start_time);
			
		completion_time[i] = start_time + burst_time[i];
		start_time = completion_time[i];
		turn_around_time[i] = completion_time[i] - arrival_time[i];
		waiting_time[i] = turn_around_time[i] - burst_time[i];
	}

	printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
	for(i = 0; i < n; i++) {
		printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", process[i], arrival_time[i], burst_time[i], completion_time[i], turn_around_time[i], waiting_time[i]);
		total_turn_around_time = total_turn_around_time + turn_around_time[i]; 
		total_waiting_time = total_waiting_time + waiting_time[i];
	}
	float average_waiting_time = (float)total_waiting_time / (float)n; 
	float average_turn_around_time = (float)total_turn_around_time / (float)n;
	
	printf("Average Turn Around Time: %f\n", average_turn_around_time);
	printf("Average Waiting Time: %f", average_waiting_time);	
}

// Implementation of Shortest Job First Scheduling
void shortest_job_first(int n, int process[], int arrival_time[], int burst_time[]) {
	int completion_time[n], turn_around_time[n], waiting_time[n];
	int total_turn_around_time = 0, total_waiting_time = 0;
	int start_time = 0, i, j;
	// Sort based on burst time
	for(i = 0; i < n; i++) {
		for(j = 0; j < n - i - 1; j++) {
			if(burst_time[j] > burst_time[j + 1]) {
				swap(burst_time[j], burst_time[j + 1]);
			}
		}			
	}

	for(i = 0; i < n; i++) {
		completion_time[i] = burst_time[i] + start_time; 
		start_time = completion_time[i];
		turn_around_time[i] = completion_time[i] - arrival_time[i];
		waiting_time[i] = turn_around_time[i] - burst_time[i];
	}
	
	printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
	for(i = 0; i < n; i++) {
		printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", process[i], arrival_time[i], burst_time[i], completion_time[i], turn_around_time[i], waiting_time[i]);
		total_turn_around_time = total_turn_around_time + turn_around_time[i]; 
		total_waiting_time = total_waiting_time + waiting_time[i];
	}
	float average_waiting_time = (float)total_waiting_time / (float)n; 
	float average_turn_around_time = (float)total_turn_around_time / (float)n;
	
	printf("Average Turn Around Time: %f\n", average_turn_around_time);
	printf("Average Waiting Time: %f", average_waiting_time);	
}

// Implementation of Round Robin Scheduling
void round_robin(int n, int process[], int arrival_time[], int burst_time[]) {
	int time_quantum, start_time = 0;
	int total_waiting_time = 0, total_turn_around_time = 0; 
	int waiting_time[n], completion_time[n], turn_around_time[n];
	int remaining_burst_time[n], i; 
	printf("Enter the time quantum: ");
	scanf("%d", &time_quantum);
	
	// Copy the burst time into a temporary array
	for(i = 0; i < n; i++) 
		remaining_burst_time[i] = burst_time[i];
	
	int done = 0; 
	// Loop until all the processes are done
	while(!done) {
		done = 1; 
		for(i = 0; i < n; i++) {
			if(remaining_burst_time[i] > 0) {
				// If remaining burst time is not 0, it means there are processes left
				done = 0;
				if(remaining_burst_time[i] > time_quantum) {
					remaining_burst_time[i] -= time_quantum; 
					start_time += time_quantum;
				} else {
					start_time = start_time + remaining_burst_time[i];
					completion_time[i] = start_time;
					turn_around_time[i] = completion_time[i] - arrival_time[i];
					waiting_time[i] = turn_around_time[i] - burst_time[i]; 
					remaining_burst_time[i] = 0;
				}
			}
		}
		if(done == 1)
			break;
	}
	
	printf("Process\tArrival Time\tBurst Time\tWaiting Time\tCompletion Time\tTurn Around Time\n");
	for(i = 0; i < n; i++) {
		printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process[i], arrival_time[i], burst_time[i], waiting_time[i], completion_time[i], turn_around_time[i]);
		total_waiting_time = total_waiting_time + waiting_time[i];
		total_turn_around_time = total_turn_around_time + turn_around_time[i];
	}
	float average_waiting_time = (float)total_waiting_time / (float)n;
	float average_turn_around_time = (float)total_turn_around_time / (float)n;
	
	printf("Average Turn Around Time: %f\n", average_turn_around_time);
	printf("Average Waiting Time: %f", average_waiting_time);
}


// Implementation of Priority Scheduling
void priority(int n, int process[], int arrival_time[], int burst_time[]) {
	int i, j;
	int completion_time[n], turn_around_time[n], waiting_time[n];
	int total_turn_around_time = 0, total_waiting_time = 0;
	int start_time = 0;
	int priority[n];
	for(i = 0; i < n; i++) {
		printf("Enter the priority of process %d: ", (i + 1)); 
		scanf("%d", &priority[i]);
	}
	// Sort Based on Priority
	for(i = 0; i < n; i++) {
		for(j = 0; j < n - i - 1; j++) {
			if(priority[j] > priority[j + 1]) {
				swap(priority[j], priority[j + 1]);
				swap(arrival_time[j], arrival_time[j + 1]);
				swap(burst_time[j], burst_time[j + 1]);
				swap(process[j], process[j + 1]);
			}
		}	
	}
	for(i = 0; i < n; i++) {
		completion_time[i] = burst_time[i] + start_time; 
		start_time = completion_time[i];
		turn_around_time[i] = completion_time[i] - arrival_time[i];
		waiting_time[i] = turn_around_time[i] - burst_time[i];
	}
	
	printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
	for(i = 0; i < n; i++) {
		printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", process[i], arrival_time[i], burst_time[i], completion_time[i], turn_around_time[i], waiting_time[i]);
		total_turn_around_time = total_turn_around_time + turn_around_time[i]; 
		total_waiting_time = total_waiting_time + waiting_time[i];
	}
	float average_waiting_time = (float)total_waiting_time / (float)n; 
	float average_turn_around_time = (float)total_turn_around_time / (float)n;
	
	printf("Average Turn Around Time: %f\n", average_turn_around_time);
	printf("Average Waiting Time: %f", average_waiting_time);	
	
}

// Main function to implement the user's choices
int main() {
	int n, choice, cont;
	printf("Enter the total number of processes: "); 
	scanf("%d", &n);
	int burst_time[n], arrival_time[n], process[n];
	int i; 
	for(i = 0; i < n; i++) {
		printf("Enter the arrival time and burst time of process %d: ", (i + 1));
		process[i] = i + 1;
		scanf("%d", &arrival_time[i]);
		scanf("%d", &burst_time[i]);
	}
	do {
		printf("1. First Come First Serve Scheduling\n2. Round Robin Scheduling\n3. Shortest Job First Scheduling\n4. Priority Scheduling\n5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1: 
				first_come_first_serve(n, process, arrival_time, burst_time);
				break;
			case 2: 
				round_robin(n, process, arrival_time, burst_time);
				break;
			case 3: 
				shortest_job_first(n, process, arrival_time, burst_time);
				break; 
			case 4: 
				priority(n, process, arrival_time, burst_time);
				break;
			case 5: 
				return 0; 
			default: 
				printf("Enter a proper choice!!");
		}
		printf("\nDo you want to continue? \n1. Yes\n0. No\n");
		scanf("%d", &cont);
	}while(cont);
	
	return 0;
}
