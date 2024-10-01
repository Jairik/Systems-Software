/* Lab 3 - Task 2
 *
 * JJ McCauley
 * Task: Copies the contents of one file to another, byte by byte. */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>


int BUFFERSIZE = 16;  // Constant buffer size

int main() {
	char buffer[BUFFERSIZE];
	umask(0);  // Clear the mask to change permissions

	// Opening file to read
	int rFile = open("demo1.txt", O_RDONLY); 	

	// Error Checking File Opening
	if(rFile < 0) {
		printf("Error Opening File");
		exit(2);

	// Creating file to write to
	int oFile = open("task2fileoutput.txt", O_CREAT|O_WRONLY, 0666);

	// Error Checking Created file to write to
	if(oFile < 0){
		printf("Error Creating File");
		exit(3);
	}

	// Reading from rFile and writing to oFile
	while (read(rFile, &buffer, 1) == 1)
		write(oFile, buffer, 1);

	// Closing files
	close(rFile);
	close(oFile);
	exit(0);
		
}
