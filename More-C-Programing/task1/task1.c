/* Lab 4 - Task 1
 * JJ McCauley
 * Task: Given 5 parameters (input file name, 4 output file names), writes the contents of the input
 * file to the other files based on the character (alphabetic, numerical, or others). Then, a copy is 
 * created from these output filses */

//Error messeage
void uhoh(char *msg){
	printf("%s", msg);
	exit(1);
}

//Four arguments in argv[]
int main(int argc, char*argv[]) {
	
	if(argc != 4)
		uhoh("ERROR - Invalid number of arguments");

	int nbyte;
	char *arg1 = argv[1]; //Input file
	char *arg2 = argv[2]; //First output file
	char *arg3 = argv[3]; //Second output file
	char *arg4 = argv[4]; //Third output file
	char *arg5 = argv[5]; //Output file to copy to 
	
	

}
