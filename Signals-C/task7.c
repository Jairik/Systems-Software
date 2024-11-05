/* Lab 7 - Task 7
 * JJ McCauley
 * Task: Intraprocess communication without signals or wait */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define iterations 1000

int main(){
	pid_t pid;

	pid = fork();
	if(pid == -1){perror("Fork error"); exit(1);}
	// Child process
	else if(pid == 0){
		while(1){
			printf("I am your child\n");
			sleep(.5);
			if(getppid() == 1){
				printf("Since my parent has completed its job, I am done too\n");
				exit(0);
			}
		}
	}
	else {  // Parent Process
		for(int i = 0; i < iterations; i++){
			printf("I am your parent\n");
			sleep(.5);
		}
		printf("My job is done\n");
	}

	exit(0);
}
