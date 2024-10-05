/* Lab 4 - Task 2
 * JJ McCauley
 * Task: Takes in an input file argument up to 80 characters and finds an integer embedded in the file, printing out the
	 argument + 10 to the standard output. 
   Note: Takes approach outlined in instructions, although convoluted (for good reason though)*/

#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#define NUM_TO_ADD 10
#define BUFFER_SIZE 1
#define MAX_INT 2147483647

void notwork(char *msg) {
	printf("%s\n", msg);
	exit(1);
}

/* Returns 1 if character c is a digit, 0 otherwise */
int isDigit(int c){
	int decValue = c - 48;
	if(decValue <= 0 || decValue >= 10) {
		return 0;
	}
	else{
		return 1;
	}
}

/* Converts integer to string */
char* intToString(int num){
	char *str;
	int curDigit, i = 0;
	while(num != 0){
		curDigit = num%10; //Get the last digit
		str[i++] = (char)curDigit + '0';
		num = num/10; //Remove the last digit
	}
	return str;
}

/* Convert string to integer*/
int stringToInt(char *c){
	if(c == NULL || c[0] == '\0'){notwork("No digits found in input file");}
	int num = ((int)c[0] - '0'), counter = 1, asciiVal;
	while(c[counter] != ' '){
		asciiVal = ((int)c[counter] - '0');
		if(asciiVal > 9 || asciiVal < 0){notwork("DEV: Invalid num");}
		if(num > (MAX_INT/10)){notwork("Int too large");}
		num = (num*10) +  asciiVal;
		counter++;
	}
	return num;
}

//1 argument: Name of input file
void main(int argc, char*argv[]){

	//Ensure valid parameters
	if(argc != 2) { notwork("Invalid number of parameters"); }
	
	int iFile, num, fileSizeCounter = 0, digitCounter = 0, nbyte;
	char buffer[BUFFER_SIZE], cNum[10] = {' '}, *finalCNum;
	
	iFile = open(argv[0], O_RDONLY);

	//Read the input file, appending to cNum if valid digit
	while((nbyte = (read(iFile, buffer, BUFFER_SIZE))) > 0){
		if(nbyte < 0){notwork("Read error");}
		if(isDigit((int)buffer[0]) == 1){
			//Append digit to c-string
			cNum[digitCounter] = buffer[0];
			digitCounter++;
			if(digitCounter >= 10){notwork("Error - Integer in file is too large");}
		}
	}

	//Convert cNum c-string to integer
	num = stringToInt(cNum);

	//Add num_to_add to integer
	num += NUM_TO_ADD;

	//Convert num back to c-String
	finalCNum = intToString(num);

	//Print to standard output using system call
	if((write(1, finalCNum, digitCounter)) < 0){notwork("Error writing to standard output");}

	exit(1);
}
