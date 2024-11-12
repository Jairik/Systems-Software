/* Lab 9 - Task 1
 * JJ McCauley
 * Task: Modify the pipe1.c from textbook, observing behavior and making small modifications to it*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


int main() {
	int data_processed;
	int file_pipes[2];
	const char some_data[] = "123";
	char buffer[BUFSIZ + 1];
	memset(buffer, '\0', sizeof(buffer));  // Fills all values of buffer with '\0'
	if (pipe(file_pipes) == 0) {  // If pipe is sucessful
		data_processed = write(file_pipes[1], some_data, strlen(some_data));
		printf("Wrote %d bytes\n", data_processed);
		data_processed = read(file_pipes[0], buffer, BUFSIZ);
		printf("Read %d bytes: %s\n", data_processed, buffer);
		exit(EXIT_SUCCESS);
	} 
	exit(EXIT_FAILURE);
}
