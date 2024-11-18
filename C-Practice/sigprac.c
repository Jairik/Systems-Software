// Practice w/ Signals

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void destroyChild(int signo){
	if(signo == SIGUSR1){
		printf("My mom said go away\n");
		_exit(0);
	}
}

void destroyParent(int signo){
	if(signo == SIGCHLD){
		exit(0);
	}
}

int main(){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		perror("Fork error"); exit(1);
	}
	else if(pid == 0){  // Child process
		while(1){
			printf("Mom! I am immortal!\n");
			signal(SIGUSR1, destroyChild);
			sleep(.5);
		}
	}
	else {  // Parent Process
		signal(SIGCHLD, destroyParent);
		int i = 0;
		while(1){
			i++;
			printf("I am parent\n");
			sleep(.5);
			if(i == 10){
				kill(pid, SIGUSR1);
			}
		}
		printf("Sorry son\n");
	}
	exit(0);
}
