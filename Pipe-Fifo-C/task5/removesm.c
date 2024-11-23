/* Lab 9 - Task 5
 * JJ McCauley
 * removesm.c: removes shared memory built by buildsm.c */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int fd1 = atoi(argv[1]);
	if(close(fd1) == -1){perror("Unlink error"); exit(1);}  // remove from memory
	printf("Pipe is removed from memory\n");
	exit(0);
}
