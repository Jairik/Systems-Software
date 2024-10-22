/* Lab 5-6 task 4
 * JJ McCauley
 * Task: Modifying task 3 to use the wait() function
 * NOTE: Explanation in task4Response file */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>  // For wait function

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
	int stat_val;

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
		case 0:  // Child case
			for(int i = 0; i < Nc; i++) {
				message = "This is the child";
				puts(message);
				sleep(Tc);
			}
			break;
		default:  // Parent case
			stat_val;
			wait(&stat_val);
			for(int i = 0; i < Np; i++){
				message = "This is the parent";
				puts(message);
				sleep(Tp);
			}
			break;
	}
	
	exit(0);
}
