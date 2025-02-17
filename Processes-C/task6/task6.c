/* Lab 5-6 Task 6
 * JJ McCauley
 * Task: Take in input file as parameter & write contents to independent files, with parent process collecting
 * numeric characters and child process collecting non-numeric characters. */

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define BUFFER_SIZE 1

//Helper function for delcaring errors
void pError(char *msg){
	printf("ERROR: %s", msg);
	exit(1); //Exit with error code
}


// Helper function to determine if char is numeric (returns 1 if true, 0 if false)
int isNumeric(char c){
	int x = (int)c - '0';
	if(x > 9 || x < 0){return 0;}
	else{return 1;}
}


// Parameter: Input file name
int main(int argc, char *argv[]){
	if(argc != 2){pError("Invalid number of parameters");}
		
	// Declare flag for syncrhonization
	int childIsDone = 0;  // Initialized to false

	// Open file once
	int fd;
	if((fd = open(argv[1], O_RDONLY)) < 0){pError("invalid file");}
	
	// Create child process
	pid_t pid = fork();

	// Declare read methods based on files
	if(pid == -1){pError("fork failed");}
	
	// Child process case
	else if(pid == 0){
		
		char buf[BUFFER_SIZE];
		int offsetC = lseek(fd, 0, SEEK_SET); //Child offset
		int ocFd = open("child.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
		
		while(read(fd, buf, BUFFER_SIZE) > 0){
			//lseek(fd, offsetC, SEEK_SET);
			if(isNumeric(buf[0]) == 0){  // Print non-numeric characters only
				if((write(ocFd, buf, BUFFER_SIZE)) < 0){pError("writing to child output file");}
				//offsetC = lseek(fd, 0, SEEK_CUR);	
			}
			else{
				//offsetC = lseek(fd, 1, SEEK_CUR);
			}

		}
		childIsDone = 1;
	}	

	// Parent process case
	else{
		
		char buf2[BUFFER_SIZE];
		int offsetP = lseek(fd, 0, SEEK_SET);
		int opFd = open("parent.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
		
		while(childIsDone == 0){usleep(50000);}  // Wait for child to complete

		lseek(fd, 0, SEEK_SET);

		while(read(fd, buf2, BUFFER_SIZE) > 0){
			//lseek(fd, offsetP, SEEK_SET);
			printf("Parent offsetP: %d\n", offsetP);
			if(isNumeric(buf2[0]) == 1) {  // Print numeric characters only
				if((write(opFd, buf2, BUFFER_SIZE)) < 0){pError("writing to parent output file");}
				//offsetP = lseek(fd, 0, SEEK_CUR);
			}
			else{
				//offsetP = lseek(fd, 1, SEEK_CUR);
			}
		}
	}
}
