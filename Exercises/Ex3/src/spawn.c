#include <unistd.h>
#include <stdio.h>

#define USAGE "Usage: spawn N \"program_name [program_name params]\""

int main(int argc, char** argv){
	if(argc != 3){
		char*  what_is_N = "N: Number of children to spawn";
		char* what_is_prog = "program_name: Name of program children will execute";
		char* what_is_prog2 = "(program name and its requisite parameters go in \"quotes\")";
		printf("%s\n\t %s\n\t %s\n\t %s\n",USAGE,what_is_N,what_is_prog,what_is_prog2);
		printf("\n\tEg.,\n\tspawn 25 \"mv file1.txt file2.txt\"\n");
	}
}
