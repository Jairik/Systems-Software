/* Lab 9 - Task 3
 * JJ McCauley
 * Task: Expanding task2 to add two-way communication between parent and child */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	int data_processed, msg_processed, status;
	int file_pipes[2], file_pipes2[2];
	const char msg[] = "Hi there, Kiddo";
	char buffer[BUFSIZ + 1];
	pid_t fork_result;

	memset(buffer, '\0', sizeof(buffer));  // Set null terminator as all values in buffer
	
	printf("PID OF PARENT: %d\n", getpid());  // DEBUGGING PURPOSES

	if(pipe(file_pipes) == 0){
		
		// Create second pipe
		if(pipe(file_pipes2) != 0){
			perror("Error creating second pipe");
			exit(1);
		}
		
		// Create child & parent process
		fork_result = fork();
		
		// Fork error
		if(fork_result < 0){
			perror("Fork failure");
			exit(1);
		}
		
		// Child process
		if(fork_result == 0){
			close(file_pipes[1]);  // Close write end of first pipe
			close(file_pipes2[0]);  // Close read end of second pipe
			sprintf(buffer, "%d", file_pipes[0]);
			(void)execl("twoPipesChild", "twoPipesChild", buffer, file_pipes[0], file_pipes2[1], (char *) 0);
			printf("exec unsuccessful\n");
			exit(1);
		}
		
		// Parent process
		else{
			close(file_pipes[0]);  // Close read end of first pipe for parent
			close(file_pipes2[1]);  // Close write end of second pipe for parent
			msg_processed = write(file_pipes[1], msg, strlen(msg));
			printf("%d - wrote %d bytes\n", getpid(), msg_processed);
			
			wait(&status);  // Wait for child to write msg to pipe

			data_processed = read(file_pipes2[0], buffer, strlen(buffer));
			printf("%d - read %d bytes\n", getpid(), data_processed);	
		}
	}	
	exit(0);
}
