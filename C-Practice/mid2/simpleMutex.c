/* Simple Mutex Problem - JJ McCauley */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// !! Defining Global Mutex Here
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int count = 0;  // Critical section to be shared by threads

void *countEvens(void *arg){
	for(int i = 0; i < 10; i++){
		if(i%2 == 0){
			pthread_mutex_lock(&mutex1); // Lock mutex from other processes
			count++;
			printf("Evens looking at %d, New Count: %d\n", i, count);
			pthread_mutex_unlock(&mutex1);  // Unlock mutex so other processes can use it
			sleep(1);
		}
	
	}
}


void *countOdds(void *arg){
	for(int i = 0; i < 10; i++){
		if(i%2 == 1){
			pthread_mutex_lock(&mutex1);
			count++;
			printf(" Odds looking at %d, New Count: %d\n", i, count);
			pthread_mutex_unlock(&mutex1);
			sleep(1);
		}
	}
}


int main(){
	// Define pthreads
	pthread_t evenThread, oddThread;
	
	// Create pthreads, associating with appropriate functions
	pthread_create(&evenThread, NULL, countEvens, NULL);
	pthread_create(&oddThread, NULL, countOdds, NULL);

	// Calling pthread_join to ensure both threads are complete
	pthread_join(evenThread, NULL);
	pthread_join(oddThread, NULL);

	printf("Final Count: %d\n", count);
}
