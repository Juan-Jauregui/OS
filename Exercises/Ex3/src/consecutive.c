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
		(void) printf("\tfilename: The name of a file with numbers)\n\n");
		return 1;
   }

	FILE *file = fopen(argv[1],"r+");
   int rv;

   int line = 0;	//Make lines 0-indexed internally (weird behavior otherwise)
	int number;

	int previousLine, previousNumber;

   /* Reads file line by line, interpreting each line as an int and storing it
    * in number. When EOF is reached, stops. */
	while((rv = fscanf(file, "%d", &number)) != EOF){
		//if previousNumber is set and it's not the same as number-1,
		if(line >= 1 && previousNumber && (previousNumber != (number-1))){
			char* spaces = "    ";  //Four spaces for Formatting
			//Print line numbers offset by 1 to match exercise specifications
			printf("%s%d: %d\n",spaces,previousLine+1,previousNumber);
			printf("%s%d: %d\n",spaces,line+1,number);
		}
		previousNumber = number++;  //update number and previousNumber
		previousLine = line++;      //Update line and previousLine
	}
	fclose(file);
	return 0;
}
