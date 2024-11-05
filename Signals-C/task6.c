/* Lab 7 - Task 6
 * JJ McCauley
 * Task: Create child and grandparent process, sending signals from parent to end execution */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

/* Signal Handlers */
void parent_handler(int sig){if(sig == SIGUSR2){exit(0);}}

void child_handler(int sig){if(sig == SIGUSR1){exit(0);}}


int main(){
	pid_t pid1, pid2;
	signal(SIGUSR2, parent_handler);
	pid_t parentPID = getpid();

	// Create child and parent process
	pid1 = fork();
	if(pid1 == -1){perror("Fork 1 error\n"); exit(1);}
	else if(pid1 == 0){  // Child process
		//Create grandchild process
		pid2 = fork();
		signal(SIGUSR1, child_handler);
		if(pid2 == -1){perror("Fork 2 error\n"); exit(1);}
		else if(pid1 == 0){  // Grandparent process
			for(int i = 0; i < 10; i++){
				printf("grandparent process\n");
			}
			kill(getppid(), SIGUSR1);
			while(1){  // Continiously check still exists 
				if(getppid() == 1){exit(0);}
			
			}
		}
		else{  // Child process
			while(1){
				printf("child process\n");
			}		
		}
	}
	else{  // Parent process 
		while(1){
			printf("parent process\n");
		}
	}
}
