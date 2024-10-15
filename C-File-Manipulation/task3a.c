/* Lab 4 - Task 3.1
 * JJ McCauley
 * Makes a directory heirchy using symbolic links */

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
	if(link("hello", "~/Systems-Software/C-File-Manipulation/homedir/Dir2/Dir21/hello") == -1){pError("Error copying file");
}
	// Create symbolic link 'toDir21' to Dir21 in Dir1
	if(symlink("~/Systems-Software/C-File-Manipulation/homedir/Dir2/Dir21", "~/Systems-Software/C-File-Manipulation/homedir/Dir1/toDir21") == -1){
		pError("Error creating symbolic link toDir21");
	}

	// Create symbolic link 'toHello' to Hello executable in Dir1/hello
	if(symlink("~/Systems-Software/C-File-Manipulation/homedir/Dir2/Dir21/hello", "~/Systems-Software/C-File-Manipulation/homedir/Dir1/toHello") == -1){
		pError("Error creating symbolic link toHello");
	}

	exit(1);
}
