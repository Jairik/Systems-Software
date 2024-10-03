/* Lab 3 - Task 8
 * JJ McCauley
 * Task: Take in an input file and output file as arguments. Then, encode each character from input file into Ascii format, then output into output file. */

#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void noooError(char *str){
	printf("%s", str);
}

//Takes in two arguments: input file (1) and output file (2)
int main(int argc, char*argv[]){
	
	if(argc < 2){
		noooError("ERROR- Less than 2 arguments");
	}

	char buffer[1];
	int ascii;
	int nbyte;

	//Get input and output files
	char *input_file = argv[1];
	char *output_file = argv[2];

	//Open input file
	int rFile = open(input_file, O_RDONLY);
	if(rFile < 0)
		noooError("Error opening input file");

	//Open output file
	int oFile = open(output_file, O_WRONLY | O_CREAT, 0666);
	if(oFile < 0)
		noooError("Error opening output file");
	
	//Redirect standard output to output file
	if (dup2(oFile, STDOUT_FILENO) == -1) {
        	noooError("Error Redirecting File Output");
    	}

	//Iterate through the rFile, reading, converting to Ascii, then writing to oFile
	while((nbyte = read(rFile, buffer, 1)) > 0) {
		ascii = (int)buffer[0];
		printf("%i", ascii);
	}
	printf("\n");

	exit(0);
}
