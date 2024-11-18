// Helper file for task2

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){
	int data_processed;
	char buffer[BUFSIZ + 1] = "123";
	int file_descriptor;
	
	sscanf(argv[1], "%d", &file_descriptor);
	
	data_processed = write(file_descriptor, buffer, BUFSIZ);
	close(file_descriptor);  // Close the pipe to add null termination to it
	printf("%d - wrote %d bytes: %s\n", getpid(), data_processed, buffer);
	exit(0);
}
