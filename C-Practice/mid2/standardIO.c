/* C program that receives a C-string (up to 80) from keyboard (standard input) and write
 * on standard output. This program keeps */


// NOTES: 0 IS THE FD FOR STANDARD INPUT

#include <stdio.h>

int main(){
	char buf[80];
	int nread;
	while((nread == read(0, buf, 80)) > 0){
		write(0, buf, nread);
	}
}
