/* Lab 5-6 child.c (helper to task 5)
 * JJ McCauley */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Helper function to exit program with error
void pError(char *msg){
	printf("ERROR: %s\n", msg);
	exit(1);
}

// Helper function that converts argument to int
int strToInt(char *c){
	int num = 0;
	for(int i = 0; c[i] != '\0'; i++){
		num = (num*10) + (c[i] - '0');
	}
	return num;
}

int main(int argc, char *argv[]){

	// Validate & get parameters
	if(argc != 4){pError("Invalid number of parameters");}
	char *message = argv[1];
	int Nc = strToInt(argv[2]);
	int Tc = strToInt(argv[3]);
	
	//Get pid
	int pid = getpid();

	// Iterate and print messages
	for(int i = 0; i < Nc; i++){
		printf("%d: %s\n", pid, message);
		sleep(Tc);
	}

	exit(37); //Use unique exit code
}
