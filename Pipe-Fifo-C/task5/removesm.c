/* Lab 9 - Task 5
 * JJ McCauley
 * removesm.c: removes shared memory built by buildsm.c */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int fd1 = atoi(argv[1]);
	unlink(fd1);  // remove from memory
}
