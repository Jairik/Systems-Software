/* Lab 4 - Task 4
 * JJ McCauley
 * Task: mv function from scratch */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stats.h>
#include <sys/types.h>

void pError(char *msg){
	printf("%s", msg);
	exit(1);
}

// Parameters: file name and path to directory
int main(int argc, char* argv[]){
	if(argc != 3){pError("Invalid number of arguments");}
	
	char *file = argv[1];
	char *path = argc[2];

	

}
