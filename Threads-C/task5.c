/* Lab 8 - Task 5
 * JJ McCauley
 * Task: Parent process takes in shell command and file name, sending the child using popen. Child will then implement
 * the command and then send to parent. Parent then will display output from child. */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE 256

// Takes in two arguments: command and filename
int main(int argc, char *argv[]){
	
	char full_command[BUFSIZE], output[BUFSIZE];
	snprintf(full_command, sizeof(full_command), "%s %s", argv[1], argv[2]);

	FILE *wfp = popen(full_command, "w");
	if(wfp == NULL){perror("popen failed :(\n"); exit(1);}
	else{
		fwrite(full_command, sizeof(char), strlen(full_command), wfp);
		pclose(wfp);
		exit(0);
	}

	exit(1);
}
