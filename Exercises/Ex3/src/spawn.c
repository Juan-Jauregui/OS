/* spawn.c
 *
 * Creates a specified number of children, each of which execute the specified
 * program with the specified arguments. Meant to demonstrate race conditions in
 * processes which interact with a common resource.
 *
 * Author: Juan Jauregui
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


#define USAGE "Usage: spawn N \"program_name [program_name params]\""
#define DEBUG 0

int main(int argc, char** argv){
	/* If not being run properly, print out usage and exit */
	if(argc != 3){
		char*  what_is_N = "N: Number of children to spawn";
		char* what_is_prog = "program_name: Name of program children will execute";
		char* what_is_prog2 = "(program name and its requisite parameters go in \"quotes\")";
		printf("%s\n\t %s\n\t %s\n\t %s\n",USAGE,what_is_N,what_is_prog,what_is_prog2);
		printf("\n\tEg.,\n\tspawn 25 \"mv file1.txt file2.txt\"\n");
		return 1;
	}

	int num_children = atoi(argv[1]);	//# of forks to perform, specified by argument
	char* tokens = strtok(argv[2]," ");	//Tokenize the program & its arguments

	char* params[10];		//Will hold subsequent tokens. 10 should be enough, right?
	params[0] = tokens;	//First param is program name. Can just copy it.

	/* Fill params[] with a null-terminated array of strings. Will be used to return
	 * execv(). The While loop's structure makes it so the array includes a NULL
	 * element at the end, but that's what execv() expects to it's cool */
	int i = 1;
	while(tokens != NULL) {
		tokens = strtok(NULL, " ");
		params[i++] = tokens;
	}

	// if(DEBUG) printf("\nSpawning %d children\n",num_children);
	// if(DEBUG) printf("\nExecuting:\n\t%s\n",program_to_execute);

	pid_t parent = getpid();	//Makes it easy to keep track of the original process
	pid_t pid;		//Will be used to know whether process is a child or not

	// if(DEBUG) printf("Parent process: %d\n",parent);

	/* Make as many children processes as specified by the given argument */
	for(int i = 0; i < num_children; i++){
		if(getpid() != parent) break;		//If not the parent process, don't fork
		pid = fork();		//Parents are allowed to fork all they want
	}

	//If the PID is < 0, There was an error while forking. Abort.
	if(pid < 0){
		printf("We've got a big forking problem here\n");
		return 1;
	}

	//For children processes, fork() returns 0. In these cases, we want to call exec()
	else if(pid == 0){
		/* Helpful debug text */
		if(DEBUG){
			printf("I am process #%d\n",getpid());
			printf("\tExecuting program named \"%s\"", params[0]);
			printf(" with parameters\n\t\t");
			int i = 0;
			while(params[i] != NULL) printf("\"%s\"\n\t\t",params[i++]);
			printf("\n");
		}
		//Execute the program specified with the parameters specified
		execv(params[0],params);
	}

	//If PID != 0, it's the Parent process:
	else {
		if(DEBUG) printf("This is parent process %d waiting for its children to wrap up...\n",getpid());
		wait(NULL);
		if(DEBUG) printf("All children done. Exiting...\n");
		printf("Done!\n");
	}

	return 0;
}
