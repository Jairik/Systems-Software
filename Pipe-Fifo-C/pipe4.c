// Helper file for task2

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){
	int data_processed, fd = atoi(argv[1]);  // (c) - Passing in read end of pipe as parameter  
	char buffer[BUFSIZ + 1];
	
	memset(buffer, '\0', sizeof(buffer));
	
	data_processed = read(fd, buffer, BUFSIZ);
	close(fd);  // (d) Closing fd of read end of pipe for child

	printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
	exit(0);
}
