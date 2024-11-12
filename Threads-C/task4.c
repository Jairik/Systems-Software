/* Lab 8 - Task 4
 * JJ McCauley
 * Task: Parent process asks for command line arguments and sends to child by using pipe. Child will add and display those
 * numbers until input from parent is EOF */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 256

int main(){
	pid_t pid;
	int mypipe[2], size;
	char buf[MAXLINE], readbuf[MAXLINE];
	if(pipe(mypipe) < 0){
		perror("Pipe failed\n"); exit(1);
	}

	pid = fork();
	if(pid < 0){perror("Fork failed"); exit(1);}
	else if(pid != 0){  // Parent process - writes to child
		printf("Enter two integers (-999 to exit):\n");
		close(mypipe[0]);  // Parent will only be writing to pipe
		while((size = read(STDIN_FILENO, buf, MAXLINE)) > 0){
			if(strncmp(buf, "-999", 4) == 0){
				// Close pipe and signal EOF
				close(mypipe[1]);
				break;
			}
			else{
				write(mypipe[1], buf, size);  // Write to pipe
			}
		}
	}
	else {  // Child process - receives message from pipe and displays it
		int n, int1, int2;
		close(mypipe[1]);  // Only used for reading
		while((n = read(mypipe[0], readbuf, MAXLINE)) > 0){
			if(sscanf(readbuf, "%d%d", &int1, &int2) == 2){
				sprintf(readbuf, "%d\n", int1 + int2);
				n = strlen(readbuf);
				if(write(STDOUT_FILENO, readbuf, n) != n){
					perror("Write error"); exit(1);
				}
			}
			else{
				perror("Invalid arguments - not integers");
				exit(1);
			}
		}
	}
}
