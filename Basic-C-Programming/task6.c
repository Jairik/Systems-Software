/* Lab 3 - Task 6
 * JJ McCauley
 * Task: Rewrite task 5 using pread() function */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void ohcrap(char *msg){
	printf("%s", msg);
	exit(1);
}

int main() {
	
	int nbyte;
	int i = 0;  //Iterator used for pread()
	char buffer[1];

	//Open Input File
	int rFile = open("reverse", O_RDONLY);
	if(rFile < 0)
		ohcrap("ERROR opening file");

	//Open Output File
	int oFile = open("task6msg", O_WRONLY | O_CREAT, 0760);
	if(oFile < 0)
		ohcrap("ERROR creating file");

	//Get the size (offset) of rFile
	int rFile_Size = lseek(rFile, 0, SEEK_END);
	if(rFile_Size == -1)
		ohcrap("cannot seek");
		
	//Read each line using pread(), writing subsequently
	for(int offset = rFile_Size-1; offset >= 0; --offset){
		if((pread(rFile, buffer, 1, offset)) == -1){
			ohcrap("Error reading file");
		}
		if((write(oFile, buffer, 1)) < 0){
			ohcrap("Error writing to file");
		}
	}


}
