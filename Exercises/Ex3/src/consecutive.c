/* consecutive.c
*
* Usage:
*    increment <file>
*
* Reads a file of numbers, one per line, and compares each two adjacent lines.
* For each line pair, If the number on the second line is not exactly 1 greater
* than the number on the first line, for each of the two lines it outputs the
* line numbers of each line and the number on it.
*
* Does not like files that do not have numbers in them.
*
* Based on increment.c by Prof. Richard Newman
*/

#include <stdio.h>

#define USAGE "Usage: consecutive filename"

int main(int argc, char *argv[]){
   if(argc != 2){
      (void) printf("\n%s\n",USAGE);
		(void) printf("(Where filename is the name of a file with numbers)\n\n");
		return 1;
   }

	FILE *file = fopen(argv[1],"r+");
   int rv;

   int line = 1;
	int number = 0;

	int previousLine, previousNumber;

   /* Reads file line by line, interpreting each line as an int and storing it
    * in number. When EOF is reached, stops. */
	while((rv = fscanf(file, "%d", &number)) != EOF){
		//if previousNumber is set and it's not the same as number-1,
		if(previousNumber && previousNumber != (number-1)){
			char* spaces = "    ";  //Four spaces for Formatting
			printf("%s%d: %d\n",spaces,previousLine,previousNumber);
			printf("%s%d: %d\n",spaces,line,number);
		}
		previousNumber = number++;  //update number and previousNumber
		previousLine = line++;      //Update line and previousLine
	}
	fclose(file);
	return 0;
}
