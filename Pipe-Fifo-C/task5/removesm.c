/* Lab 9 - Task 5
 * JJ McCauley
 * removesm.c: removes shared memory built by buildsm.c */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include "header.h"

int main(){
	key_t key;
	int shmid;
	struct Memory shm;
	
	// Get the shared memory id
	if((shmid = shmget(key, sizeof(struct Memory), 0)) < 0){perror("shmget error"); exit(1);}

	// Remove the shared memory
	shmctl(shmid, IPC_RMID, NULL);
	
	exit(0);  // Return with success  
}
