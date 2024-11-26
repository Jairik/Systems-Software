/* Lab 9 - Task 5
 * JJ McCauley
 * buildsm.c: Builds a shared memory to be used for interprocess communication */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <unistd.h>
#include "header.h"

int main(){
	
	int shmid;
	key_t key;
	struct Memory *shm;

	key = ftok(".", 'x');  // Creating a key value
	
	// Creating shared memory
	if((shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666)) < 0){perror("shmget error"); exit(1);}

	// Attach to shared memory
	if((long)(shm = (struct Memory *) shmat(shmid, NULL, 0)) == -1){perror("shmat error"); exit(1);}

	// Set attributes of shared memory
	shm->status = NOT_READY;
	shm->gostop = GO;
	exit(0);  // Exit with success
}
