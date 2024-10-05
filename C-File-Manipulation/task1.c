/* Lab 4 - Task 1
 * JJ McCauley
 * Task: Take in 5 parameters: input, and 4 output files. Will then write to the 4 output files in the following schema:
 * 	2) Alphabetic Characters	3) Numerical Characters		4) Other Characters
 * While parameter 5 is a copy of the input file, created by reading files 2, 3, and 4 */

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h> //Not technically needed, but cleans up code

#define BUFFER_SIZE 1

void dangiterror(char *str){
	printf("%s\n", str);
	exit(1);  //Exit with failure
}

//Helper function that returns whether the character is alphabetic
bool isAlphabetic(char c){
	int ascii = (int) c;
	if(ascii > 64 && ascii < 91) { return true; }  //Uppercase Letters
	else if(ascii > 96 && ascii < 123) { return true; }  //Lowercase Letters
	else { return false; }
}

//Helper function that returns whether the character is numeric
bool isNumeric(char c){
	int ascii = (int) c;
	return((ascii > 47) && (ascii < 58));
}

int main(int argc, char *argv[]){
	int nbyte;
	char buffer[BUFFER_SIZE];
	char tempBuffer[BUFFER_SIZE];  //Temporary buffer used when writing
	tempBuffer[0] = ' '; 
       	int inputFile, alphaFile, numFile, otherFile, copyFile;	

	//Check for correct number of parameters
	if(argc != 6){ dangiterror("Incorrect number of parameters - please enter 5"); }

	//Open input file
	if((inputFile = open(argv[1], O_RDONLY)) < 0){ dangiterror("Error Opening input file"); }

	//Opening output files
	if((alphaFile = open(argv[2], O_WRONLY | O_CREAT)) < 0){ dangiterror("Error Opening First Output Parameter"); }
	if((numFile = open(argv[3], O_WRONLY | O_CREAT)) < 0){ dangiterror("Error Opening Second Output Parameter"); }
	if((otherFile = open(argv[4], O_WRONLY | O_CREAT)) < 0){ dangiterror("Error Opening Third Output Parameter"); }
	if((copyFile = open(argv[5], O_WRONLY | O_CREAT)) < 0){ dangiterror("Error Opening Fourth Output Parameter"); }

	//Read from input file and write (either correct type character or a space) to output file 1-3
	while((nbyte = read(inputFile, buffer, BUFFER_SIZE)) > 0){
		if(isAlphabetic(buffer[0])){
			if((write(alphaFile, buffer, BUFFER_SIZE)) < 0 || (write(numFile, tempBuffer, BUFFER_SIZE)) < 0 ||
					(write(otherFile, tempBuffer, BUFFER_SIZE)) < 0)
				dangiterror("Error writing alphabetic character");
		} else if(isNumeric(buffer[0])){
                        if((write(alphaFile, tempBuffer, BUFFER_SIZE)) < 0 || (write(numFile, buffer, BUFFER_SIZE)) < 0 ||
                                        (write(otherFile, tempBuffer, BUFFER_SIZE)) < 0)
                                dangiterror("Error writing alphabetic character");
                } else{
                        if((write(alphaFile, tempBuffer, BUFFER_SIZE)) < 0 || (write(numFile, tempBuffer, BUFFER_SIZE)) < 0 ||
                                        (write(otherFile, buffer, BUFFER_SIZE)) < 0)
                                dangiterror("Error writing alphabetic character");
                }
	}

	//Getting size of file to loop again
	off_t offset = lseek(inputFile, 0, SEEK_END);

	//Create the copy file by looping through the first 3 output files
	for(int i = 0; i < offset; i++) {
		if((read(alphaFile, buffer, BUFFER_SIZE)) < 0) { dangiterror("Output 1 Read Error"); }
		if(buffer[0] != ' ') { //If it is not a space, valid character and write
			if((write(copyFile, buffer, BUFFER_SIZE)) < 0) { dangiterror("Copy write error"); }
			continue; //Skip the rest of the logic and go to the next iteration
		}
		offset--;
		if((read(numFile, buffer, BUFFER_SIZE)) < 0) { dangiterror("Output 2 Read Error"); }
                if(buffer[0] != ' ') { //If it is not a space, valid character and write
                        if((write(copyFile, buffer, BUFFER_SIZE)) < 0) { dangiterror("Copy write error"); }
                        continue; //Skip the rest of the logic and go to the next iteration
                }
                offset--;
		if((read(otherFile, buffer, BUFFER_SIZE)) < 0) { dangiterror("Output 3 Read Error"); }
		//If it reached this point, it must be an 'other' character so we can write it
		if((write(copyFile, buffer, BUFFER_SIZE)) < 0) { dangiterror("Copy write error"); }
	}
}
