/* Lab 7 task 1
 * JJ McCauley
 * Task: Modify the provided program to use sigaction */

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


// Signal handler for SIGALARM
void ding(int sig){
	printf("Ding!\n");
}

int main(){
	// Starting application and setting up sigaction listener
	pid_t pid;
	printf("alarm application starting\n");
	struct sigaction act;
	act.sa_handler = ding;
	if(sigaction(SIGUSR1, &act, 0) == -1){perror("Sigaction error");}

	// 
	pid = fork();
	switch(pid){
		case -1: // Failure
			perror("Fork failed");
			exit(1);
		case 0: // Child case
			sleep(5);
			kill(getppid(), SIGUSR1);
			exit(0);
	}

	// Only the parent process should be at this point
	printf("Waiting for alarm to go off\n");
	pause();

	printf("Done\n");
	exit(0);
}
