#include "find.h"
#include <stdio.h>
#include <string.h>

// The 'searchMethod' is of type void and takes a number of arguments
// It takes the word I am looking for, the current line of text, the original text,
// the number of matches, the number of the current line, the file pointer to write to and the file name to write to
void searchMethod(char *word, char *line, char* originalText, int *numberOfMatches, int *numberOfLine, FILE *fPointerWrite, char *writeFileName){
	int textLength = strlen(line);
	int wordLength = strlen(word);
	int posText = 0;
	int start = 0;
	*numberOfMatches = 0;
	// This for loop goes through the whole line of text
	for (int index=0;index<textLength;index++){
		// It compares every character of the line with the characters of the searching word
		if (word[posText] == line[index]){
			// If there is a match I increment the 'posText' by one
			posText += 1;
			// If the word I am looking for is in the text that line means that at the value of 'posText' will be equal to the 'wordLength' I am looking for
			// This check allowes me to look for substrings. For example, if I have "thereisnotime" and I am looking for "time", it will print the whole phrase - "thereisnotime"
			if (posText == wordLength){
				// When there is a match I increment the 'numberOfMatches' variable which is returned to the main method as pointer
				*numberOfMatches += 1;
				// If this is the first match for the line, I will print this message
				if (*numberOfMatches == 1){
					fprintf(fPointerWrite,"\tFound match(es) on line %d: ",*numberOfLine);
				}
				// I store the current index, where the word ends
				start = index;
				// Using the while loop I go back to the beginnig of the phrase
				while (line[start-1] != ' ' && start-1 >= 0)
					start -= 1;
				// Using this while loop I print every character of the found phrase
				while (line[start] != ' ' && line[start]!='\n' && line[start] != '\0'){
					fprintf(fPointerWrite, "%c",originalText[start]);
					start += 1;
				}
				// I separete the different matches with space ' '
				fprintf(fPointerWrite, "  ");
				// Once I have printed everything I set the 'posText' to 0, as now I looking for new match
				posText = 0;
			}
		}
		// If the current letter of the searching word is different from the current letter from the line
		// That means that the current phrase is not the same. So the 'posText' is set to 0 - the beginning of the searching word
		else {
			posText = 0;
		}
	}
	// If there were matches I print a new line character in order to format the output
	if (*numberOfMatches != 0)
		fprintf(fPointerWrite, "\n");
}

// The 'ignoreCaseMethod' is of type void and takes a string and converts every letter to lower case
void ignoreCaseMethod(char *word){
	// I get the length of the word
	int wordlength = strlen(word);
	// This for loop convers every letter to lower case using the method 'tolower'
	for (int i = 0; i < wordlength; i++)
		word[i] = tolower(word[i]);
}