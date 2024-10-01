/* Lab 3 - Task 3
 *
 * JJ McCauley
 * Task: Copies contents of a source file to a destination file using a buffer of 32 bytes, 
 * with the output file having permissions of rwx-rwx---*/

#include <unistd.h>  //For read() write() close(0 functions
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>  //For open() and O_ constands
#include <sys/stat.h>  //For file permission constants

int main() {
	//Initialize the buffer
	int BUFFER_SIZE = 32;	
	char buffer[BUFFER_SIZE];
	int nbyte;

	//Open the file to read
	int nread = open("demo2.txt", O_RDONLY);
	if( nread < 0) {
		printf("ERROR- Unable to open file");
		exit(2);
	}

	//Create new file to write to using write command
	int nwrite = open("demo2_copy.txt", O_WRONLY | O_CREAT, 0770);
	if (nwrite < 0){
		printf("ERROR- Unable to open write file");
		exit(3);
	}

	//Read in the files to the buffer, then write to new file
	while((nbyte = read(nread, buffer, BUFFER_SIZE)) > 0)
		if (write(nwrite, buffer, nbyte) != nbyte)
			printf("WRITE ERROR");
	if (nbyte < 0) {
		printf("READ ERROR");
		exit(4);
	}

	exit(0);

}
