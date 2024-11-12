/* Lab 8 - Task 3
 * JJ McCauley
 * Task: Threads and Thread Termination to do a bunch of stuff */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  // For sleep function

// Clean-up handler for thread1
void Bye(void *arg){
	pthread_t originalThread = *(pthread_t *) arg;
	printf("Bye!\n");
	pthread_cancel(originalThread);
}

// Clean-up handler for original thread
void Bye1(void *arg){
	printf("END OF PROGRAM\n");
	exit(0);
}

void *thread1(void *arg){
	// Push cleanup function
	pthread_cleanup_push(Bye, arg);
	while(1){
		printf("In the first thread\n");
		usleep(500000);  // Cancellation point
	}
	pthread_cleanup_pop(0);
}

void *thread2(void *arg){
	pthread_t thr1 = *(pthread_t *) arg;
	int i = 0;
	while(1){
		printf("In the second thread\n");
		usleep(500000); // Cancellation point
		i++;
		if(i == 10){
			// Terminate first thread
			pthread_cancel(thr1);
		}
	}
}

int main(){

	// Initialize threads
	pthread_t t1, t2, curT;
	int rc1, rc2;
	// Create cleanup function for original thread
	pthread_cleanup_push(Bye1, NULL);
	// Get current thread
	curT = pthread_self();

	rc1 = pthread_create(&t1, NULL, thread1, &curT);
	if(rc1 < 0){perror("Error creating first thread\n"); exit(1);}

	rc2 = pthread_create(&t2, NULL, thread2, &t1);
       	if(rc2 < 0){perror("Error creating second thread\n"); exit(1);}

	// Perform original thread actions
	while(1){
		usleep(500000); // Cancellation point
		printf("In the original thread\n");
	}
	pthread_cleanup_pop(0);	

}
