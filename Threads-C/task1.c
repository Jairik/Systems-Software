/* Lab 8 - Task 1
 * JJ McCauley
 * Task: Concurrent Calculations - Program accepts integer argument and calculates the sum up and factorial 
 * using multi-threading */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *sumUp(void *arg){
	int n = *(int *) arg;
	int i = 1, sum = 0;
	while(i <= n){
		sum += i;
		i++;
	}
	printf("Total Sum: %d\n", sum);
}

void *factorial(void *arg){
	int n = *(int *) arg;
	int i = 2, total = 1;
	while(i <= n){
		total *= i;
		i++;
	}
	printf("Total Factorial: %d\n", total);
}

// Takes in one integer argument
int main(int argc, char *argv[]){
	// Validate & Convert Int Parameter
	if(argc != 2){perror("Invalid num parameters"); exit(1);}
	int num = atoi(argv[1]);
	if(num == 0){perror("Error with parameter/type conversion"); exit(1);}
	
	// Create variables to hold sum and total
	int sum, total;

	// Create two processes 
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, sumUp, &num);  // Create Sum-up process
	pthread_create(&thread2, NULL, factorial, &num); // Factorial process

	// Wait for processes to finish
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
}
