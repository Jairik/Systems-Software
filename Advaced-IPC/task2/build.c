/* Lab 10 - Task 2
 * JJ McCauley
 * Task: Create shared memory space for saving 5 integers (array) */

#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "header.h"


int main(){
	int shmid;  // Shared memory ID
	key_t key;
	struct Memory *shm;

	// Creating the key
	key = ftok(".", 't');

	// Creating the shared memory
	if((shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666)) < 0){
		perror("shmget error\n");
		exit(1);
	}

	// Attach the Memory struct to shared memory
	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if((long) shm == -1){perror("shmat error\n"); exit(1);}

	// Setting status flags
	shm->status = NOT_READY;
	shm->gostop = GO;
	
	exit(0);
}
