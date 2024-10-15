/* Lab 4 - Task 3
 * JJ McCauley
 * Task: Take in a file name as parameter and check if it contains a palindrome (file consists of only lowercase alphabetic letters). */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BSIZE 1  // Defining Buffer Size

void pError(char *msg){
	printf("%s\n", msg);
	exit(1); //Exit with error code
}

/* Palindrome Function: Returns 1 if contents of file descriptor is palindrome, else returns 0
 * Parameters: Duplicate file descriptors
 * Returns: 1 on isPalindrome, 0 if not*/
int palind(int fd1, int fd2){
	char buf1[BSIZE], buf2[BSIZE];  // Buffers & temporary characters for comparison
	int offsetForward = lseek(fd1, 0, SEEK_SET);  // Setting fd1 to read forward
	int middle = (offsetForward/2)+1;  // Creating middle to see if this works
	int offsetBackward = lseek(fd2, -2, SEEK_END);	// Setting fd2 to read backward
	int cForward, cBackward;
	while(offsetForward != middle){
		if((cForward = read(fd1, buf1, BSIZE)) < 0){pError("Error reading file (fd1)");}
		if((cBackward = read(fd2, buf2, BSIZE)) < 0){pError("Error reading file (fd2)");}
		if(buf1[0] != buf2[0]){return 0;}  // Counterargument found, not palindrome
		lseek(fd2, -2, SEEK_CUR);  // Move file 'cursor' back 2 to make up for read
		// Updating offsets for conditional
		offsetForward++;
	}	
	return 1;  // No counterarguments found, contents forms a palindrome
}

// Takes file as argument
int main(int argc, char *argv[]){
	if(argc != 2){pError("Invalid number of parameters");}
	int openFd, newfd, result;
	if((openFd = open(argv[1], O_RDONLY, 0666)) < 0) {pError("Error opening file");}

	//Create duplicate file descriptor 
	if((newfd = open(argv[1], O_RDONLY, 0666)) == -1){pError("Error duplicating file descriptor");}
	
	//Call & test palind function
	result = palind(openFd, newfd);
	if(result == 1){
		printf("File is a palindrome!\n");
	}
	else{
		printf("File is not a palindrome... :(\n");
	}
	exit(0);

}
