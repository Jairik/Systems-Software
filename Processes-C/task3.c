/* Lab 5-6 task 3
 * JJ McCauley
 * Task: Using fork1.c from BLP 4th Edition page 474, modifying it to take in command line arguments */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Helper function to exit program with error
void pError(char *msg){
	printf("ERROR: %s", msg);
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


/* Arguments:
 * Nc - Number of iterations for child process
 * Np - Number of iterations for parent process
 * Tc - Sleep time for child process
 * Tp - Sleep time for parent process */
int main(int argc, char *argv[]){
	
	//Ensuring that correct number of arguments was provided
	if(argc != 5){pError("Invalid number of arguments provided");}

	pid_t pid;
	char *message;

	// Assigning arguments to int variables
	int Nc = strToInt(argv[1]);
	int Np = strToInt(argv[2]);
	int Tc = strToInt(argv[3]);
	int Tp = strToInt(argv[4]);

	printf("fork program starting\n");
	pid = fork();
	
	switch(pid){
		case -1:
			pError("fork failed");
			exit(1);
		case 0:
			for(int i = 0; i < Nc; i++) {
				message = "This is the child";
				puts(message);
				sleep(Tc);
			}
			break;
		default:
			for(int i = 0; i < Np; i++){
				message = "This is the parent";
				puts(message);
				sleep(Tp);
			}
			break;
	}
	
	/*for(; n > 0; n--) {
		puts(message);
		sleep(1);
	}*/
	
	
	exit(0);
}
