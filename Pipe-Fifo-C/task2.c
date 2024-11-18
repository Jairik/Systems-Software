/* Lab 9 - Task 2
 * JJ McCauley
 * Task: Modifying example code to see pipes across a fork/exec */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	int data_processed, status;
	int file_pipes[2];
	const char some_data[] = "123";
	char buffer[BUFSIZ + 1];
	pid_t fork_result;

	memset(buffer, '\0', sizeof(buffer));  // Set null terminator as all values in buffer
	
	if(pipe(file_pipes) == 0){
		fork_result = fork();
		// Fork error
		if(fork_result < 0){
			perror("Fork failure");
			exit(1);
		}
		// Child process
		if(fork_result == 0){
			close(file_pipes[0]);
			sprintf(buffer, "%d", file_pipes[1]);
			(void)execl("pipe4", "pipe4", file_pipes[1], (char *) 0);
			exit(1);
		}
		// Parent process
		else{
			close(file_pipes[1]);  // Close write end of pipe for parent
			wait(&status);  // Parent waits for child
			data_processed = read(file_pipes[0], buffer, strlen(buffer));
			printf("%d - read %d bytes\n", getpid(), data_processed);
		}
	}	
	exit(0);
}
