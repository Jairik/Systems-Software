/* Lab 5-6 Task 2
 * JJ McCauley
 * Task: Read the utmp file and count number of USER_PROCESS records 
 * Note: Use 'who' command to verify output */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <utmp.h>


// Print error function
void pError(char *msg){
	printf("%s\n", msg);
	exit(1);
}


// Opens utmp file and returns file descriptor
int openUtmpFile(struct utmp ut){
	int fd = open(_PATH_UTMP, O_RDONLY);
	if(fd == -1){pError("Error opening utmp file");}
	return fd;
}


// use openUtmp function & count number records in USER_PROCESS
void main(){
	struct utmp ut;
	const int utmp_size = sizeof(struct utmp);
	// Create buffer of type utmp to hold each individual record while reading
	struct utmp buffer[utmp_size];
	// Open utmp file
	int utmpFd = openUtmpFile(ut), count = 0;
	if(utmpFd < 0){pError("Error opening utmp file");}

	// Loop through contents to find USER_PROCESS
	while((read(utmpFd, buffer, utmp_size)) == utmp_size){
		if(buffer->ut_type == USER_PROCESS){
			//Print the username and increment count
			printf("Username: %s\n", buffer[0].ut_user);
			count++;
		}
	}
	
	// Print count and exit program
	printf("Total number of user_process records: %d\n", count);
	exit(0);
}
