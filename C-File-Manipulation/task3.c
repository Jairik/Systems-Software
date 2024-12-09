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
	char buf1, buf2;  // Buffers & temporary characters for comparison
	int offsetForward = lseek(fd1, 0, SEEK_SET);  // Setting fd1 to read forward
	int middle = ((lseek(fd2, 0, SEEK_END))/2);  // Setting offset middle
	int offsetBackward = lseek(fd2, -2, SEEK_END);	// Setting fd2 to read backward
	int cForward, cBackward, counter = 0;
	printf("Offset center: %d\n", middle);
	printf("Scanning for palindrome...\n");
	while(counter <= middle){
		// Read forward
		offsetForward = lseek(fd1, counter, SEEK_SET);
		printf("Current forward offset: %d\n", counter);
		if((cForward = read(fd1, &buf1, BSIZE)) < 0){pError("Error reading file (fd1)");}
		printf("Reading %c from fd1 buf\n", buf1);
		
		// Read backward
		offsetBackward = lseek(fd2, (-1 * (counter+2)), SEEK_END);
		printf("Current backwards offset: %d\n", offsetBackward);
		if((cBackward = read(fd2, &buf2, BSIZE)) < 0){pError("Error reading file (fd2)");}
		printf("Reading %c from fd2 buf\n", buf2);
		
		// Compare characters and increment counter for next iteration
		if(buf1 != buf2){printf("Counterargument Found! %c vs %c\n", buf1, buf2); return 0;}  // Counterargument found, not palindrome
		counter++;
	}	
	return 1;  // No counterarguments found, contents forms a palindrome
}

// Takes file as argument
int main(int argc, char *argv[]){
	if(argc != 2){pError("Invalid number of parameters");}
	int openFd, newfd, result;
	if((openFd = open(argv[1], O_RDONLY, 0666)) < 0) {pError("Error opening file");}

	//Create duplicate file descriptor
	// --- ADD DUP TO MAKE WORK -- 
	if((newfd = dup(openFd)) == -1){pError("Error duplicating file descriptor");}
	
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
