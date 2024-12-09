/* By using popen, let a child runs previous program and send data to parent to pipe. If inputes are two integer values, calculate sum of two numbers and write result on standard output. If inputs are not two integer values, it must respond as "incalid inputs: two integers". This program keeps running until the child process's termination */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	char buf[80];
	int num1, num2;
	FILE *filePtr = popen("./standardIO", "r");
	int fd = fileno(filePtr);
	while(read(fd, buf, 80)){
		if(sscanf(buf, "%d%d", &num1, &num2) == 2){
			printf("%d\n", num1+num2);
		}
		else{
			printf("Invalid inputs: two integers\n");
		}
	}
	exit(0);
}
