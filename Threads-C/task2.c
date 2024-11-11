/* Lab 8 - Task 2
 * JJ McCauley
 * Task: Wait for a thread for concurrent calculations */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int *arr;  // Global integer array
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex to lock array (critical selection) to avoid race condition
typedef struct{int argc; char **argv;} input_args;  // Struct to pass in additional parameters to first function

// Takes in a struct of argc, argv, and reads in the test scores
void *getTestScores(void *args){
	// Get arguments from parameterized struct
	input_args *arguments = (input_args *) args;  // Cast to struct
	int argc = arguments->argc;
	char **argv = arguments->argv;
	
	// Allocate memory for arr based on size
	arr = malloc((argc-1) * sizeof(int));
	if(arr == NULL){perror("Memory Allocation Failed"); exit(1);}

	// Check number of arguments
	if(argc == 1 || argc > 21){perror("Invalid number of arguments"); exit(1);}

	// Load into arr
	for(int i = 1; i < argc; i++){
		arr[i-1] = atoi(argv[i]);
	}
}

// Calculates the average and middle with argc as parameter
void *calcAvg(void *argc){
	pthread_mutex_lock(&mutex);  // Lock mutex while sorting list
	int size = *(int *) argc;
	size--; // Not account for program name in arguments
	
	// Using bubble sort to sort array
	for (int i = 0; i < size - 1; i++) {
        	for (int j = 0; j < size - i - 1; j++) {
            		if (arr[j] > arr[j + 1]) {
                		int temp = arr[j];
                		arr[j] = arr[j + 1];
                		arr[j + 1] = temp;
            		}
        	}
    	}
	pthread_mutex_unlock(&mutex);  // Unlock for other processes to use
	
	// Find average and middle
	int total = 0, avg, middle;
	for(int n = 0; n < size; n++){
		total += arr[n];
	}
	avg = total/size;
	if(size%2 == 1){middle = arr[(size/2)];}  // Odd number of elements
	else{  // Even number of elements, must average middle two numbers
		middle = (arr[size/2] + arr[(size/2)+1])/2;
	}
	printf("Average: %d\nMiddle: %d\n", avg, middle);
}

// Calculates the min and max of dataset (sorted), given argc
void *calcMinMax(void *argc){
	int size = *(int *) argc;
	size--;
	int min = arr[0], max = arr[size-1];
	printf("Min: %d\nMax: %d\n", min, max);
}

// Clear buffer and set to 0
void *clearBuf(void *argc){
	int size = *(int *) argc;
	size--; // Account for program name in argc
	
	// Clearing array
	for(int i = 0; i < size; i++){
		arr[i] = 0;
	}

	// Displaying cleared array
	printf("Cleared Array:");
	for(int j = 0; j < size; j++){
		printf(" %d", arr[j]);
	}
	printf("\n");
	free(arr); arr = NULL;
}

// Takes in up to 20 int arguments
int main(int argc, char *argv[]){
	// Create struct to pass into first thread
	input_args d;
	d.argc = argc;
	d.argv = argv;

	// Create & Synchronize Threads
	pthread_t thread1, thread2, thread3, thread4;
	pthread_create(&thread1, NULL, getTestScores, &d);
	pthread_join(thread1, NULL); //Ensure thread1 completes first
	
	// Run threads 2 and 3, ensuring they finish before moving on
	pthread_create(&thread2, NULL, calcAvg, &argc);
	pthread_create(&thread3, NULL, calcMinMax, &argc);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	// Run thread 4 once others are finished
	pthread_create(&thread4, NULL, clearBuf, &argc);
	pthread_join(thread4, NULL);
}
