/* Lab 9 - Task 1
 * JJ McCauley
 * Task: Modify the pipe1.c from textbook, observing behavior and making small modifications to it*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

// Global Integer Constants
const int READ_END = 0;
const int WRITE_END = 1;

int main() {
	int data_processed;
	int file_pipes[2];
	const char some_data[] = "123";
	
	char *buffer = (char *) malloc((strlen(some_data) + 1) * sizeof(char));  // Dynamically allocate space for buffer
	
	memset(buffer, '\0', sizeof(buffer));  // Fills all values of buffer with '\0'
	
	if (pipe(file_pipes) == 0) {  // If pipe is sucessful
		
		data_processed = write(file_pipes[WRITE_END], some_data, strlen(some_data));
		strcpy(buffer, some_data);
		printf("Wrote %d bytes\n", data_processed);
		
		data_processed = read(file_pipes[READ_END], buffer, strlen(buffer));
		printf("Read %d bytes: %s\n", data_processed, buffer);
		
		exit(EXIT_SUCCESS);
	} 
	exit(EXIT_FAILURE);
}
