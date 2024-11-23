/* Lab 9 - Task 5
 * JJ McCauley
 * process1.c: Sends two integer values into shared memory until end of data */

#include <stdio.h>
#include <stdlib.h>

// Helper function to determine if two given c-strings is an integer
// NOTE: Just realized that this function is completely useless but I don't want to delete it because I now have emotional attachment to it (idek if it works)
int isInt(char *c1, char *c2){
	int i = 0, j = 0;
	if(c1 == NULL || c2 == NULL){return 0;}
	while(c1[i] != NULL){
		if(c1[i] - '0' <= 0 || c1[i] - '0' > 9){
			return 0;
		}
		i++;
	}
	while(c2[j] != NULL){
		if(c2[j] - '0' <= 0 || c2[j] - '0' > 9){
			return 0;
		}
		j++;
	}
	return 1;
}

/* Takes in one parameter: Pipe file descriptor */
int main(int argc, char *argv[]){
	if(argc != 2){perror("Invalid number of arguments"); exit(1);}

	char buf[BUFSIZ];
	int tempNumBuf[2];
	int fd = atoi(argv[1]);  // Get file descriptor for pipe
	
	// Reading integers from standard output and feeding into pipe
	while(read(0, buf, BUFSIZ) > 0){
		if(sscanf(buf, "%d%d", tempNumBuf[0], tempNumBuf[1]) == 2){  // If two valid numbers
			if(write(fd, buf, BUFSIZ) < 0){perror("Write error in process 1"); exit(1);}
		}
		else{
			printf("Invalid Arguments\n");
		}

	}
	close(fd);  // Close write end
	exit(0);  // Successfully exit program
}
