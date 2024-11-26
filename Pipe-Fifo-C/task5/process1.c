/* Lab 9 - Task 5
 * JJ McCauley
 * process1.c: Sends two integer values into shared memory until end of data */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include "header.h"

int main(){

	int shmid, r;
	key_t key;
	struct Memory *shm;
	int num1, num2;
	char buf[BUFSIZ];

	// Get the shared memory key value & open shared memory
	key = ftok(".", 'x'); 
	if((shmid = shmget(key, sizeof(struct Memory), 0)) < 0){perror("shmget error"); exit(1);}

	// Attach to shared memory
	shm = (struct Memory *) shmat(shmid, NULL, 0);
	if((long) shm == -1){perror("shmat error"); exit(1);}

	// Set flags
	shm->gostop = GO;
	shm->status = NOT_READY;
	printf("Enter two integers\n");
	while(r = (read(STDIN_FILENO, buf, BUFSIZ)) > 0){
		if(sscanf(buf, "%d%d", &num1, &num2) == 2){  // If two valid numbers
			// Assign numbers to shared memory
			shm->data.num1 = num1;
			shm->data.num2 = num2;
			// Assign flag to indicate shared memory is filled
			shm->status = FILLED;
			// Wait until receiver receives input
			while(shm->status != TAKEN){;}

		}
		else{
			printf("Invalid Arguments\n");
		}
		printf("Enter two integers of CTRL-D to stop\n");
	}

	// Set stop flag & detach from shared memory
	shm->gostop = STOP;
	shmdt((void *) shm);  // Detach
	exit(0);
}
