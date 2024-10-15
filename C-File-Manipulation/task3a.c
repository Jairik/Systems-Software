/* Lab 4 - Task 3.1
 * JJ McCauley
 * Makes a directory heirchy using symbolic lunks */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void pError(char *msg){
	printf("%s", msg);
	exit(1);  // Exit w/ error message
}


int main(){
	// --- Create directory structure ---
	// Home Directory (Made inside current folder to not clutter home directory)
	if(mkdir("~/Systems-Software/C-File-Manipulation/homedir") == -1){pError("Error creating home directory");}
	// Dir1
	if(mkdir("~/Systems-Software/C-File-Manipulation/homedir/Dir1") == -1){pError("Error creating Dir1");}
	// Dir 2
	if(mkdir("~/Systems-Software/C-File-Manipulation/homedir/Dir2") == -1){pError("Error creating Dir2");}
	//Dir 21
	if(mkdir("~/Systems-Software/C-File-Manipulation/homedir/Dir2/Dir21") == -1){pError("Error creating Dir21");}

	// Copy hello file under Dir21 (copy by byte)
	int openfd = open("hello", O_RDONLY, 0666);
	int copyfd = open("hello", )
	

}
