/* Lab 9 - Task 5
 * JJ McCauley
 * process2.c: retreives two integers from shared memory and displays the sum of two integers */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXSIZE 256

/* Parameters: Read end of pipe */
int main(int argc, char *argv[]){
	if(argc != 2){perror("Invalid number of arguments"); exit(1);}

	char buf[BUFSIZ];
	int fd = atoi(argv[1]);  // Get read end of pipe
	int num1, num2;
	
	printf("Inside process 2\n");
	
	int r;
	while((r = read(fd, buf, BUFSIZ)) > 0){
		sscanf(buf, "%d%d", &num1, &num2);
		printf("Sum: %d\n", (num1+num2));
		printf("Attempting to read fd: %s\n", buf);
		*buf = "";  // Clearing buffer
	}

	printf("Process 2 done reading\n");
	close(fd);
	printf("Process 2 closed fd");
	execl("removesm", "removesm", (void *) 0);  // Call program to remove shared memory
	exit(0);
}
