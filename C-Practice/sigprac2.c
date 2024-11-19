// Trying sigprac exercise again from memory
/* Notes to self: */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


void childSigHandler(int signo){
	if(signo == SIGUSR1){
		printf("Child process end statement\n");
		_exit(0);  // Exit current process
	}
}

void parentSigHandler(int signo){
	if(signo == SIGCHLD){
		printf("Parent process end statement\n");
		exit(0);  // Successful termination
	}
}

void main(){
	
	pid_t fd = fork();

	if(fd == -1){perror("Error forking"); exit(1);}
	else if(fd == 0){  // Child process
		signal(SIGUSR1, childSigHandler);
		// Print indefinitely until signal is retreived
		while(1){
			printf("I am child and immortal!\n");
			sleep(1);
		}		
	}
	else{  // Parent process
		int counter = 0;
		signal(SIGCHLD, parentSigHandler);
		while(1){
			printf("In parent process\n");
			counter++;
			if(counter == 10){
				kill(fd, SIGUSR1);
			}
			sleep(1);
		}
	}
	exit(1);  // If it reaches this point, failed termination
}

