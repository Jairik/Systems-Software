/* Lab 10 - Task 2
 * JJ McCauley
 * Task: Acts as producer in Producer-Consumer problem */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#include "header.h"

// Simple helper function that returns number 1-10
int getRand(){
	return (rand()%10)+1;
}

int main(){
	int shmid;  // Shared memory ID
	key_t key;
	struct Memory *shm;
	char name[20];
	int randInt, arrIndex;

	// Opening shared memory
	key = ftok(".", 't');  // Getting key value
	if((shmid = shmget(key, sizeof(struct Memory), 0)) < 0){
		perror("shmget error\n");
		exit(1);
	}
	
	// Attaching shared memory
	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if((long) shm == -1){perror("shmat error\n"); exit(1);}

	// Initially setting flags
	shm->gostop = GO;
	shm->status = NOT_READY;

	// Setting initial index to 0 to start
	shm->data.arrIndex = 0;

	// Adding random numbers to buffer forever
	while(1){
		printf("inside while loop in producer\n");
		usleep(500000);
		randInt = getRand();
		while(shm->status == FILLED){
			printf("Shared Memory is full, producer waits...\n");
			usleep(50000);  // Wait until the green light is given from receiver
		}
		while(shm->blocked == 1){;}  // Wait while blocked
		// Place the random integer in array and update index
		shm->blocked = 1;
		while((arrIndex = shm->data.arrIndex) > 4){usleep(500);}  // Wait until int is in range
		printf("DEBUGGING CURRENT INDEX: %d\n", arrIndex);
		shm->data.arr[arrIndex] = randInt;
		shm->data.arrIndex = ++arrIndex;
		shm->blocked = 0;

		// Set filled flag if necessary
		if(arrIndex == 5){
			shm->status = FILLED;
			printf("Shared Memory is FILLED by producer\n");
			usleep(50000);
		}

		// Print contents of shared memory
		shm->blocked = 1;
		printf("Shared Memory contents from PRODUCER: ");
		for(int i = 0; i <= arrIndex; i++){
			printf(" %d", shm->data.arr[i]);
		}
		printf("\n");
		shm->blocked = 0;
	}

	shm->gostop = STOP;  // Stop the receiver process

	exit(0);
}
