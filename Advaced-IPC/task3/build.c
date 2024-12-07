/* Lab 10 - Task 3
 * JJ McCauley
 * Task: Create shared memory space for saving 5 integers (array) and create semaphore structure with 3 members */

#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string.h>  // For memset
#include "header.h"

union senum{
	int val;  // Used for SETVAL
	struct semid_ds *buf;  // For IPC_STAT and IPC_SET
	unsigned short *array;  // For GETALL and SETALL
};

int main(){
	int shmid, semid;  // Shared memory ID and Semaphore ID
	key_t keyShm, keySem;  // Key for shared memory and semaphore
	struct Memory *shm;
	union senum arg;

	// Creating the shared memory key
	keyShm = ftok(".", 't');

	// Creating the shared memory
	if((shmid = shmget(keyShm, sizeof(struct Memory), IPC_CREAT | 0666)) < 0){
		perror("shmget error\n");
		exit(1);
	}

	// Attach the Memory struct to shared memory
	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if((long) shm == -1){perror("shmat error\n"); exit(1);}

	/* Creating Semaphore */
	// Creating the key
	keySem = ftok(".", 's');
	if(keySem == -1){perror("ftok error\n"); exit(1);}

	// Creating a semaphore set with 3 semaphores
	if((semid = semget(keySem, 3, 0666 | IPC_CREAT)) == -1){
		perror("Semget error\n");
		exit(1);
	}

	// Initialize value of first semaphore (Mutex)
	arg.val = 1;
	if(semctl(semid, MUTEX, SETVAL, arg) == -1){
		perror("Error in semctl first semaphore\n");
		exit(1);
	}

	// Initialize value of second semaphore (Filled)
	arg.val = 0;
	if(semctl(semid, FULL, SETVAL, arg) == -1){
		perror("Error in semctl second semaphore\n");
		exit(1);
	}	

	// Initialize value of third semaphore (Empty)
	arg.val = ARRSIZE;
	if(semctl(semid, EMPTY, SETVAL, arg) == -1){
		perror("Error in semctl third semaphore\n");
		exit(1);
	}

	// Setting every value in array to 0
	memset(shm->data.arr, 0, sizeof(shm->data.arr));

	// Setting status flags
	shm->gostop = GO;
	
	exit(0);
}
