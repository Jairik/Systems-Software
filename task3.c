/* Lab 3 - Task 3
 *
 * JJ McCauley
 * Task: Copies contents of a source file to a destination file using a buffer of 32 bytes, 
 * with the output file having permissions of rwx-rwx---*/

#include <unistd.h>
#include <stdlib.h>

int main() {
	//Initialize the buffer
	int BUFFER_SIZE = 32;	
	char buffer[BUFFER_SIZE];

	//Read in the file
	int nread = open("demo2.txt");
	if( nread < 0) {
		printf("ERROR- Unable to open file");
		error(2);
	}

	//Create new file to write to using write command
	int nwrite = write("demo2_copy.txt", 

}
