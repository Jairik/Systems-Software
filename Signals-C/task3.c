/* Lab 7 - Task 3
 * JJ McCauley
 * Task: Communicate between child and parent without sending signal, only low-level system calls */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define bufferSize 7

int main(){

	// Declare basic variables
	char buf[bufferSize] = "Hi, Mom", msg[bufferSize];  // Loading message
	int fd, pid, status;
	
	// Open file for parent and child
	fd = open("foo", O_CREAT | O_TRUNC | O_RDWR, 0666);

	// Create child process
	pid = fork();

	if(pid == -1){perror("Fork error"); exit(1);}
	// Child case
	else if(pid == 0){
		write(fd, buf, bufferSize);
	}
	// Parent case
	else{
		int childPID = wait(&status);  // Waiting for child process to end
		lseek(fd, 0, SEEK_SET);  // Resetting the beggining of file
		read(fd, msg, bufferSize);  // Reading message from file
		printf("My son said %s\n", msg);  // Printing message
	}

	close(fd);
	exit(0);
}
