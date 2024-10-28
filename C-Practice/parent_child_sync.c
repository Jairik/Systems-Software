/* Practice Activity - JJ McCauley
 * Task: Write a C program for sharing a file between parent and child, with both processes creating a copy of the file */

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv){
	if(argc > 2){perror("Too  many arguments");}
	const int bsize = 1;
	char buf[bsize];
	int fd = open(argv[1], O_RDONLY, 0666);
	int end = lseek(fd, 0, SEEK_END);
	int pid = fork();
	if(pid == -1){perror("Fork error");}
	
	// Child Process
	else if(pid == 0){
		int co = open("child.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
		int offset = lseek(fd, 0, SEEK_SET);
		while(offset < end){
			lseek(fd, offset, SEEK_SET); //Resetting lseek
			read(fd, buf, bsize);
			write(co, buf, bsize);
			offset = lseek(fd, 0, SEEK_CUR);  // Setting child offset
		}
		exit(0);
	}

	// Parent Process
	else{
		int po = open("parent.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
		int offset = lseek(fd, 0, SEEK_SET);
		while(offset < end){
			lseek(fd, offset, SEEK_SET);
			read(fd, buf, bsize);
			write(po, buf, bsize);
			offset = lseek(fd, 0, SEEK_CUR);
		}
		exit(0);
	}

	exit(0);


}
