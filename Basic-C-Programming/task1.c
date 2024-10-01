/* Lab 3- Task 1
 * JJ McCauley
 * Task: Copies the contents of one file to another file using only standard input */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 2

void error(char *msg){
	printf("%s", msg);
	exit(1);
}

int main() {
	int nbyte;
	char buffer[BUFFER_SIZE];

	while((nbyte = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
		if(write(STDOUT_FILENO, buffer, nbyte) != nbyte)
			error("Write Error");
	}

	if(nbyte < 0)
		error("Read Error");

	exit(0);
}
