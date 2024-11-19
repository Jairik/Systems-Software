/* Creating a zombie process for practice - JJ McCauley
 * Zombie Process: Where the child has terminated, but the parent has not called wait() to retreive it's
 * exit status. This leaves a small portion of the process floating in memory space (thus, child is zombie). */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	pid_t pid = fork();
	if(pid < 0){perror("Fork error"); exit(1);}
	// --- CHILD PROCESS ---
	else if(pid == 0){
		sleep(3);  // Sleep for 3 seconds
		printf("Child exiting\n");
		_exit(0);
	}
	// --- PARENT PROCESS ---
	else{
		for(int i = 0; i < 10; i++){
			sleep(1);
			printf("I am parent\n");
		}
	}

	exit(0);
}
