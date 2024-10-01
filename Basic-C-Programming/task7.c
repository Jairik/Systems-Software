/* Lab 3 - Task 7
 * JJ McCauley
 * Task: Receive a sequence of integers via the command line and print their sum */

#include <stdio.h>
#include <stdlib.h>

void lO(char *msg){
	printf("%s", msg);
	exit(1);	
}

int strToInt(char *str){
	int result = 0, num;
	//Loop through until end of character
	for(int i = 0; str[i] != '\0'; i++){
		if((num = str[i] - '0') > 9)
			lO("ERROR- Invalid Character");
		result = result * 10 + num;  //Convert each to ascii
	}
	return result;
}

//Arguments: agrc (number of arguments passed), argv[] (pointer array to c-string of each argument)
int main(int argc, char*argv[]) {

	int sum = 0;

	//Loop through all arguments, converting to int and adding to sum
	for(int i = 1; i < argc; i++){
		sum += strToInt(argv[i]);
	}

	//Print the result
	printf("%d", sum);
	printf("\n");

	exit(0);
}
