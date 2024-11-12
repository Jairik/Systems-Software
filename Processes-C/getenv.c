/* Lab 5-6 Task 1
 * JJ McCauley
 * Task: Create getenv function from scratch */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>  // Used for strlen function

extern char **environ;

// Print error function
void e(char *msg){
	printf("%s\n", msg);
	exit(1);
}

char *mygetenv(const char *name){

	int nameLen = strlen(name), j = 0; 
	
	// Get reference to environment variables
	char **p = environ;
	
	// Iterate through all environment variables, returning the one equal to name
	for(int i = 0; p[i] != NULL; i++){
		// Determine if current c-string is the one we are looking for
		j = 0;
		while(name[j] != '\0' && p[i][j] != '\0' && name[j] == p[i][j]){j++;}
		if(name[j] == '\0' && p[i][j] == '='){
			return p[i] + j + 1;
		}
	}
	return NULL;  // If not found, return NULL
}



// Test getenv function
void main(int argc, char *argv[]){
	char *path = mygetenv(argv[1]);
	printf("Path: %s\n\n", path);
	
	exit(0);
}
