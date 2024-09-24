/* Lab 3 - Task 2
 *
 * JJ McCauley
 * Task: Copies the contents of one file to another, byte by byte. */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int BUFFERSIZE = 16;  // Constant buffer size

int main() {
	char buffer[BUFFERSIZE];

	// Opening file to read
	int rFile = open("demo1.txt", 1); 
	
	// Creating file to write to
	int oFile = creat("task2fileoutput.txt");
	
	// Reading from rFile and writing to oFile
	while (read(rFile, buffer, 1) == 1)
		write(oFile, buffer, 1);

	// Closing files
	close(rFile);
	close(oFile);
	exit(0);
	
}
