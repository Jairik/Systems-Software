//JJ Practice - Uses positional parameters, dup/dup2, pread and pwrite

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char*argv[]){
	int fs, nr, nr2, nw, nw2;
	int fd = open("output1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	printf("Hello new file");	
}
