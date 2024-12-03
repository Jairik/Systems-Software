/* Lab 10 - Task 2
 * JJ McCauley
 * Task: Act as receiver for shared memory, removing numbers from shared memory */

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include "header.h"

int main(){
	int shmid, index;
	key_t key;
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

	// Read & Remove integers from shared memory
	while(shm->gostop == GO){
		
		// Checking if array is empty
		while(shm->data.arrIndex == 0){
			usleep(500000);
		}

		index = shm->data.arrIndex;
		shm->data.arr[index] = 0;  // Remove from the array
		if(index > 0){
			shm->data.arrIndex = --index; 
		}
		else{
			shm->data.arrIndex = 0;  // Array is empty, ensure that it doesn't go past 0
		}

		// Print contents of shared memory
		printf("Shared Memory contents from RECEIVER: ");
		for(int i = 0; i < index; i++){
			printf(" %d", shm->data.arr[i]);
		}

		shm->status = TAKEN; 

		printf("\n\n");
		usleep(500000);
	}

	// Once here, remove shared memory
	shmctl(shmid, IPC_RMID, NULL);
	exit(0);

}
