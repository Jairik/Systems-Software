/* Lab 4 - Task 2
 * JJ McCauley
 * Task: Takes in an input file argument up to 80 characters and finds an integer embedded in the file, printing out the
	 argument + 10 to the standard output. */

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
int isDigit(char c){
	if(c >= '0' && c <= '9') {
		return 1; //It is a digit
	}
	else{
		return 0; //It is not a digit
	}
}

/* Converts integer to string */
char* intToString(int num){
	char *str = malloc(12), *tempStr = malloc(12);
	int curDigit, i = 0;
	while(num != 0){
		curDigit = num%10; //Get the last digit
		tempStr[i++] = (char)(curDigit + '0');
		num = num/10; //Remove the last digit
	}
	//Un-reverse string
	for(int j = 0; j < i; j++){
		str[j] = tempStr[i-j-1];
	}
	str[i] = '\0';  // Add null terminator at end
	free(tempStr);
	return str;
}

/* Convert string to integer*/
int stringToInt(char *c){
	if(c == NULL || c[0] == '\0'){notwork("No digits found in input file");}
	int num = 0, counter = 0, asciiVal;
	while(counter < strlen(c)){
		asciiVal = c[counter] - '0';  //Convert char to string
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
	
	iFile = open(argv[1], O_RDONLY);

	//Read the input file, appending to cNum if valid digit
	while((nbyte = (read(iFile, buffer, BUFFER_SIZE))) > 0){
		if(nbyte < 0){notwork("Read error");}
		if((isDigit(buffer[0])) == 1){
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

	exit(0);
}
