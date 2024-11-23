/* Lab 9 - Task 5
 * JJ McCauley
 * buildsm.c: Builds a shared memory to be used for interprocess communication (using pipe, however FIFO could also be used) */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	int fd[2];  // Initializing pipe
	if(pipe(fd) < 0){perror("Pipe Error"); exit(1);}  // Create the pipe
	
	// Create c-strings to hold file descriptors to make them valid arguments
	char fd0Str[10], fd1Str[10];
	sprintf(fd0Str, "%d", fd[0]);
	sprintf(fd1Str, "%d", fd[1]);
	
	// Create parent and child to run process1 and process2
	pid_t pid = fork();

	if(pid < 0){perror("Fork Error"); exit(1);}
	
	else if(pid == 0){  // Child case
		printf("Executing Process 1\n");
		execl("./process1", "process1", fd1Str, (void *) 0);
		exit(1);  // Exit if execl failure
	}

	else{  // Parent case
		pid_t pid2 = fork();
		if(pid2 < 0){perror("Fork Error 2"); exit(1);}
		else if(pid2 == 0){ // Child case
			printf("Executing Process 2\n");
			execl("./process2", "process2", fd0Str, (void *) 0);
			exit(1);  // Exit if execl failure
		}
		else{ // Parent case- wait for them to finish then call removesm
			close(fd[0]);
			close(fd[1]);
			wait(NULL);
			wait(NULL);
			
			execl("removesm", "removesm", fd, (void *) 0);
		}
	}
	
	exit(0); //Successful termination
}
