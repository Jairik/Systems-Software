/* Lab 9 - Task 5
 * JJ McCauley
 * process2.c: retreives two integers from shared memory and displays the sum of two integers */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/* Parameters: Read end of pipe */
int main(int argc, char *argv[]){
	if(argc != 2){perror("Invalid number of arguments"); exit(1);}

	char buf[BUFSIZ];
	int fd = argv[1];  // Get read end of pipe
	int num1, num2;

	while(read(fd, buf, BUFSIZ) > 0){
		sscanf(buf, "%d%d", num1, num2);
		printf("Sum: %d\n", (num1+num2));
	}
	close(fd);
	execl("removesm", "removesm", (void *) 0);  // Call program to remove shared memory
	exit(0);
}
