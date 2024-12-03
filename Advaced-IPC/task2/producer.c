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
	int randInt, index;

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
	while(shm->gostop == GO){
		randInt = getRand();
		while(shm->status == FILLED){
			printf("Shared Memory is full, producer waits...\n");
			usleep(500000);  // Wait until the green light is given from receiver
		}
		
		// Place the random integer in array and update index
		index = shm->data.arrIndex;
		shm->data.arr[index] = randInt;
		shm->data.arrIndex = ++index;
		
		// Update flag if buffer is full
		if(index >= 5){
			shm->status = FILLED;
		}

		// Print contents of shared memory
		printf("Shared Memory contents from PRODUCER: ");
		for(int i = 0; i < index; i++){
			printf(" %d", shm->data.arr[i]);
		}
		printf("\n\n");
		usleep(500000);
	}

	shm->gostop = STOP;  // Stop the receiver process

	exit(0);
}
