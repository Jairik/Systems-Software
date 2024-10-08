/* Lab 3 - Task 5
 * JJ McCauley
 * Task: Writes the data of a given file in reverse to another file */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void whoops(char *msg){
	printf("%s",msg);
	exit(1);
}


int main(int argc, char*argv[]) {
	int nbyte;
	char buffer[1];

	//Open the file to write in reverse	
	int rFile = open(argv[1], O_RDONLY);
	if(rFile < 0){
		whoops("Unable to open file to reverse");
	}

	//Create file to write to
	int oFile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0760);

	//Get the last position of the file using lseek
	off_t offset = lseek(rFile, 0, SEEK_END);
	if(offset == -1){
		whoops("Initital lseek error");
	}

	//Iterate backwards in the read file and write the output
	while(offset > 0){
		offset = lseek(rFile, -1, SEEK_CUR);
		if(read(rFile, buffer, 1) != 1)
			whoops("Read ERROR");
		if(write(oFile, buffer, 1) != 1)
			whoops("Write ERROR");
		if(offset == 0)  //Make it exit instead of infinitely printing
			break;
		offset = lseek(rFile, -1, SEEK_CUR); //Move pointer back after reading
	}

	//close(rFile); close(oFile);

	exit(0);
}
