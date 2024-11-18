// Helper file for task3

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){

	if(argc < 3){
		perror("Invalid number of arguments\n");
		exit(1);
	}

	int data_processed, msg_processed;
	char buffer[BUFSIZ + 1], *msg = "Hi, Mom";
	int pipe1, pipe2;
	
	memset(buffer, '\0', sizeof(buffer));
	
	sscanf(argv[1], "%d", &pipe1);
	sscanf(argv[2], "%d", &pipe2);
	
	// Reading message from pipe (received from parent)
	data_processed = read(pipe1, buffer, BUFSIZ);
	if(data_processed <= 0){perror("Error reading from pipe1");}
	printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
	
	// Write message to pipe (sending to parent)
	msg_processed = write(pipe2, msg, strlen(msg));
	if(msg_processed <= 0){perror("Error reading from pipe2");}
	printf("%d - wrote %d bytes: %s\n", getpid(), msg_processed, msg);

	exit(0);
}
