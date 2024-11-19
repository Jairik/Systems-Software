/* Thread Practice and whatnot */


// KEY: PASS VARIABLE BY REFERENCE TO PTHREAD_CREATE FUNCTIONS TO UPDATE ACTUAL VALUE

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


// Add 10
void *thread1act(void *arg){
	int *num = (int *) arg;
	*num = *num + 10;
	printf("Num after adding 10: %d\n", *num);
	return num;
}

// Add 20
void *thread2act(void *arg){
	int *num = (int *) arg;
	*num += 20;
	printf("Num after adding 20: %d\n", *num);
	return num;  //idk ab this fr
}

// Add 30
void *thread3act(void *arg){
	int *num = (int *) arg;
	*num += 30;
	printf("Num after adding 30: %d\n", *num);
	return num;
}


int main(){
	pthread_t thread1, thread2, thread3;
	int rNum = 0;
	int rt = pthread_create(&thread1, NULL, thread1act, &rNum);
	if(rt < 0){perror("Error creating 1st thread\n"); exit(1);}
	pthread_join(thread1, NULL);

	int rt2 = pthread_create(&thread2, NULL, thread2act, &rNum);
	if(rt2 < 0){perror("Error creating 2nd thread\n"); exit(1);}
	pthread_join(thread2, NULL);

	int rt3 = pthread_create(&thread3, NULL, thread3act, &rNum);
	if(rt3 < 0){perror("Error creating 3rd thread\n"); exit(1);}
	pthread_join(thread3, NULL);

	printf("Final num from main: %d\n", rNum);


}
