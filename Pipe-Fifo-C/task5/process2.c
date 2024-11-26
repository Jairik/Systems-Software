/* Lab 9 - Task 5
 * JJ McCauley
 * process2.c: retreives two integers from shared memory and displays the sum of two integers */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "header.h"

#define MAXSIZE 256


int main(){

	int shmid, num1, num2;
	key_t key;
	struct Memory *shm;

	// Get key value & open existing shared memory
	key = ftok(".", 'x');  // Get key value
	if((shmid = shmget(key, sizeof(struct Memory), 0)) < 0){perror("shmget error"); exit(1);}
	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if((long)shm == -1){perror("shmat error"); exit(1);}
	
	// Calculate sums while go flag
	while(shm->gostop == GO){
		while(shm->status != FILLED){
			if(shm->gostop == STOP){break;}
			;
		}
		num1 = shm->data.num1;
		num2 = shm->data.num2;
		printf("Sum: %d\n", (num1+num2));
		shm->status = TAKEN;
	}
	
	// Detach shared memory
	shmdt((void *) shm);

	exit(0);
}
