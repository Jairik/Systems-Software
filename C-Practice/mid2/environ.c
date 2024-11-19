/* Practice using environment global variable - JJ */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern char **environ;  // This 'imports' the list of environment variables (list of strings\list of a list of chars)

int main(int argc, char *argv[]){
	char **environmentStuff = environ;

	while(*environmentStuff != NULL){
		printf("%s (%p)\n", *environmentStuff, *environmentStuff);
		*environmentStuff++; // Move onto next environment variable
	}

	exit(0); // Successful termination
}
