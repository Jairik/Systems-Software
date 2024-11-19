// Doing the first thread practice over again
/* Notes to self:
 * - pthread_create requires for thread to be passed w/ &
 * - Passing variable with '&' will change it's actual value (passed by reference)
 * - Ensure to add '*' to ptrs when printing them 			*/


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Adding 10 to the num
void *func1(void *arg){
	int *val = (int *) arg;
	*val += 10;
	printf("Number after adding 10: %d\n", *val);
}

// Adding 20 to num
void *func2(void *arg){
	int *val = (int *) arg;
	*val += 20;
	printf("Number after adding 20: %d\n", *val);
}

// Adding 30 to num
void *func3(void *arg){
	int *val = (int *) arg;
	*val += 30;
	printf("Number after adding 30: %d\n", *val);
}

void checkrt(int rt){
	if(rt < 0){
		perror("Error creating thread\n");
		exit(1);
	}
}

void main(){
	pthread_t thread1, thread2, thread3;
	int rt1, rt2, rt3;
	int num = 0;

	// Create first thread
	rt1 = pthread_create(&thread1, NULL, func1, &num);
	checkrt(rt1);
	pthread_join(thread1, NULL);

	// Create second thread
	rt2 = pthread_create(&thread2, NULL, func2, &num);
	checkrt(rt2);
	pthread_join(thread2, NULL);

	//Create third thread
	rt3 = pthread_create(&thread3, NULL, func3, &num);
	checkrt(rt3);
	pthread_join(thread3, NULL);

	// Print final result
	printf("Final Result: %d", num);

}
