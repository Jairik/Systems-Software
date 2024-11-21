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
		else if(fork_result == 0){
			sprintf(buffer, "%d", file_pipes[0]);
			(void)execl("pipe4", "pipe4", buffer, (char *) 0);
			exit(1);
		}
		// Parent process
		else{
			data_processed = write(file_pipes[1], some_data, strlen(some_data));
			printf("%d - wrote %d bytes\n", getpid(), data_processed);
		}
	}	
	exit(0);
}
