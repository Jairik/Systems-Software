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

//Convert int to char
char int_to_char(int digit){
	//return digit + '\0';
	return digit;
}

//Takes in two arguments: input file (1) and output file (2)
int main(int argc, char*argv[]){
	
	if(argc < 2){
		noooError("ERROR- Less than 2 arguments");
	}

	char buffer[1];
	char ascii_str[10];  //Hold the ascii string value
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

	//Iterate through the rFile, reading, converting to Ascii, then writing to oFile
	while((nbyte = read(rFile, buffer, 1)) > 0) {
		buffer[0] = int_to_char((int)buffer[0]);
		if((write(oFile, buffer, 1)) < 0){
			noooError("Error writing to file");
		}
	}

	exit(0);
}
