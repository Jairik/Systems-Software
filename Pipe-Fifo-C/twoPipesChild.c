// Helper file for task3

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){

	int data_processed, msg_processed;
	char buffer[BUFSIZ + 1], *msg = "Hi, Mom";
	int pipe1, pipe2;
	
	memset(buffer, '\0', sizeof(buffer));
	
	sscanf(argv[2], "%d", &pipe1);
	sscanf(argv[3], "%d", &pipe2);
	
	// Reading message from pipe (received from parent)
	data_processed = read(pipe1, buffer, BUFSIZ);
	printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
	
	// Write message to pipe (sending to parent)
	msg_processed = write(pipe2, msg, strlen(msg));
	printf("%d - wrote %d bytes: %s\n", getpid(), msg_processed, msg);

	exit(0);
}
