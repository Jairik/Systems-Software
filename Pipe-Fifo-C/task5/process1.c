/* Lab 9 - Task 5
 * JJ McCauley
 * process1.c: Sends two integer values into shared memory until end of data */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Takes in one parameter: Pipe file descriptor */
int main(int argc, char *argv[]){
	if(argc != 2){perror("Invalid number of arguments"); exit(1);}

	char buf[BUFSIZ];
	int tempNumBuf[2];
	int fd = atoi(argv[1]);  // Get file descriptor for pipe
	
	// Reading integers from standard output and feeding into pipe
	int r;
	while(r = (read(STDIN_FILENO, buf, BUFSIZ)) > 0){
		if(sscanf(buf, "%d%d", &tempNumBuf[0], &tempNumBuf[1]) == 2){  // If two valid numbers
			if(write(fd, buf, BUFSIZ) < 0){perror("Write error in process 1"); exit(1);}
		}
		else{
			printf("Invalid Arguments\n");
		}

	}
	printf("End of File reached\n");
	if(close(fd) == -1){perror("Process 1: Error closing file descriptor"); exit(1);}  // Close write end
	printf("Process 1 closed fd\n");
	exit(0);  // Successfully exit program
}
