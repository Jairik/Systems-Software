/* Lab 10 - Task 3
 * JJ McCauley
 * Task: Act as receiver for shared memory, removing numbers from shared memory with use of Semaphore */

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include "header.h"

void down(int semid, int index){
	struct sembuf buf = {index, -1, 0};
	semop(semid, &buf, 1);
}

void up(int semid, int index){
	struct sembuf buf = {index, 1, 0};
	semop(semid, &buf, 1);
}


int main(){
	int shmid, semid, index;
	key_t key, semKey;
	struct Memory *shm;

	// Get key value & open shared memory
	key = ftok(".", 't');
	if((shmid = shmget(key, sizeof(struct Memory), 0)) < 0){
		perror("shmget error\n");
		exit(1);
	}

	// Get pointer attached to shared memory
	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if((long) shm == -1){perror("shmat error\n"); exit(1);}

	// Get key value & open semaphore
	semKey = ftok(".", 's');
	if((semid = semget(semKey, 3, 0666)) == -1){
		perror("semget error\n");
		exit(1);
	}


	// Read & Remove integers from shared memory
	while(1){
		
		// Checking if array is empty (FULL=0) or if is blocked
		while(semctl(semid, 2, GETVAL) == 0){
			usleep(1000);  // Sleep for a lil
		}
		
		down(semid, 2);  // Decrement full
		down(semid, 0);  // Decrement Mutex to 0
		index = semctl(semid, 2, GETVAL);
		shm->data.arr[--index] = 0;  // Remove from the array
		
		// Print contents of shared memory
		printf("Shared Memory contents from RECEIVER: ");
		for(int i = 0; i <= index; i++){
			printf(" %d", shm->data.arr[i]);
		}
		printf("\n");
		up(semid, 0);  // Increment mutex back to 1
		up(semid, 1);  // Increment empty 
		
		usleep(500000);
	}

	exit(0);

}
