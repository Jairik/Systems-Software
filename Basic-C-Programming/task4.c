/* Lab 3 - Task 4
 * JJ McCauley
 * Task: Appends the contents of two files to a third file with permissions rwxrw--- */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

void uhoh(char *str){
	printf("%s",str);
	exit(1);
}

int main() {
	
	int nbyte, nbyte2;
	char buffer[1];

	//Open foo1 and foo2
	int foo1Open = open("foo1.txt", O_RDONLY);
	int foo2Open = open("foo2.txt", O_RDONLY);
	if(foo1Open < 0 || foo2Open < 0){
		uhoh("ERROR Unable to open foo1 or foo2");
	}

	//Open & Create foo12
	int foo12Open = open("foo12.txt", O_WRONLY | O_CREAT, 0760);
	if(foo12Open < 0){
		uhoh("ERROR Unable to open foo12");
	}

	//Write foo1 and get offset
	while(( nbyte = read(foo1Open, buffer, 1)) > 0){
		if (write(foo12Open, buffer, nbyte) != nbyte)
                	uhoh("WRITE ERROR");
	}	
	off_t end_of_first_file = lseek(foo12Open, 0, SEEK_END);
	if(end_of_first_file == -1)
		uhoh("lseek Error");

	//Start writing at end of foo1
	while((nbyte2 = read(foo2Open, buffer, 1)) > 0) {
		if(write(foo12Open, buffer, nbyte2) != nbyte2)
			uhoh("ERROR");
	}
	if(nbyte2 < 0)
		uhoh("WRITE ERROR");

	exit(0);
	

}
