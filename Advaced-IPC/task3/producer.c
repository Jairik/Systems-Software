/* Lab 10 - Task 3
 * JJ McCauley
 * Task: Acts as producer in Producer-Consumer problem (this time, using MUTEX & Semaphores)*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include "header.h"

// Simple helper function that returns number 1-10
int getRand(){
	return (rand()%10)+1;
}

// Helper function which decrements semaphore
void down(int semid, int index){
	struct sembuf buf = {index, -1, 0};
	semop(semid, &buf, 1);
}

// Helper function which increments semaphore
void up(int semid, int index){
	struct sembuf buf = {index, 1, 0};
	semop(semid, &buf, 1);
}

int main(){
	int shmid, semid;  // Shared memory & Semaphor ID
	key_t key, semKey;  // Key for shared memory & semaphor
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

	// Opening Semaphore
	semKey = ftok(".", 's');
	if((semid = semget(semKey, 3, 0666)) == -1){
		printf("semget Error\n");
		exit(1);
	}

	// Initially setting flags
	shm->gostop = GO;

	// Adding random numbers to buffer forever
	while(1){
		randInt = getRand();
		
		down(semid, EMPTY);  // Decrement Empty Set
		down(semid, MUTEX);  // Decrement the Mutex to 0
		
		// Insert the item
		arrIndex = semctl(semid, FULL, GETVAL);
		//arrIndex = (ARRSIZE - arrIndex) % ARRSIZE;
		shm->data.arr[arrIndex] = randInt;

		// Print contents of shared memory
		printf("Shared Memory contents from PRODUCER: ");
		for(int i = 0; i < ARRSIZE; i++){
			int value = shm->data.arr[i];
			if(value == 0){printf(" _");}  // Skip removed elements
			else{printf(" %d", value);}
		}
		printf("\n");

		up(semid, MUTEX);  // Increment the Mutex back to 1 (unlock critical section)
		up(semid, FULL);  // Increment Full Set
		usleep(500000);
	}

	shm->gostop = STOP;  // Stop the receiver process

	exit(0);
}
