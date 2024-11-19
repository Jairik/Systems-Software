/* Pracitice with Orphan Processes - JJ McCauley
 * An orphan process is where the parent dies, leaving for the child to be inherited by PID 1. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	pid_t pid = fork();

	if(pid < 0){perror("Fork error"); exit(1);}

	// CHILD PROCESS
	else if(pid == 0){
		for(int i = 0; i < 10; i++){
			printf("Child Process to: %d\n", getppid());
			sleep(1);
		}
		exit(0);
	}

	// PARENT PROCESS - dies before child is done executing
	else{
		for(int i = 0; i < 3; i++){
			printf("Parent Process\n");
			sleep(1);
		}
		exit(0);
	}
}
