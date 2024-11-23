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
	// Create parent and child to run process1 and process2
	pid_t pid = fork();

	if(pid < 0){perror("Fork Error"); exit(1);}
	
	else if(pid == 0){  // Child case
		execl("process1", "process1", fd[1], (void *) 0);
		exit(1);  // Exit if execl failure
	}

	else{  // Parent case
		pid_t pid2 = fork();
		if(pid2 < 0){perror("Fork Error 2"); exit(1);}
		else if(pid2 == 0){ // Child case
			execl("process2", "process2", fd[0], (void *) 0);
			exit(1);  // Exit if execl failure
		}
		else{ // Parent case- wait for them to finish then call removesm
			waitpid(pid2, NULL, 0);
			execl("removesm", "removesm", fd, (void *) 0);
		}
	}
	
	exit(0); //Successful termination
}
