#include "find.h"
#include <stdio.h>
#include <string.h>

// The 'searchMethod' is of type void and takes a number of arguments
// It takes the word I am looking for, the current line of text, the original text,
// the number of matches, the number of the current line, the file pointer to write to and the file name to write to
void searchMethod(char *word, char *line, char* originalText, int *numberOfMatches, int *numberOfLine, FILE *fPointerWrite, char *writeFileName){
	int textLength = strlen(line);
	int wordLength = strlen(word);
	int searchingWordIndex = 0;
	int startIndex = 0;
	// At the start of every line the 'numberOfMatches' is 0
	*numberOfMatches = 0;
	// This for loop goes through the whole line of text
	for (int index=0;index<textLength;index++){
		// It compares every character of the line with the characters of the searching word
		if (word[searchingWordIndex] == line[index]){
			// If there is a match I increment the 'searchingWordIndex' by one
			searchingWordIndex += 1;
			// If the word I am looking for is in the text that means that the value of 'searchingWordIndex' will be equal to the 'wordLength' I am looking for
			// This check allowes me to look for substrings. For example, if I have "brotherhood" and I am looking for "brother", it will print the whole word - "brotherhood"
			if (searchingWordIndex == wordLength){
				// When there is a match I increment the 'numberOfMatches' variable which is returned to the main method as pointer
				*numberOfMatches += 1;
				// If this is the first match for the line, I will print this message
				if (*numberOfMatches == 1){
					fprintf(fPointerWrite,"\tFound match(es) on line %d: ",*numberOfLine);
				}
				// I store the current 'index' of the line, where the last character of the searching word occures
				// For example, if I look for "brother" in "brotherhood" I will store the index of the second 'r' in "brotherhood"
				startIndex = index;
				// Using the while loop I go back to the beginnig of the word
				while (line[startIndex-1] != ' ' && startIndex-1 >= 0){
					startIndex -= 1;
				}
				// Using this while loop I print every character of the found word until I reach space, new line or the end of the line
				while (line[startIndex] != ' ' && line[startIndex]!='\n' && line[startIndex] != '\0'){
					fprintf(fPointerWrite, "%c",originalText[startIndex]);
					startIndex += 1;
				}
				// I separate the different matches with space ' '
				fprintf(fPointerWrite, "  ");
				// Once I have printed everything I set the 'searchingWordIndex' to 0, as now I looking for a new match
				searchingWordIndex = 0;
			}
		}
		// If the current letter of the searching word is different from the current letter from the line that means that the current word is not the same.
		else {
			// If 'searchingWordIndex' is greater than zero, that means that only part of the word matched. In order not to miss the next letter I subtract one from the 'index'.
			// For example, if I look for "brother" and I search in "brotbrother" once I reach the second 'b' of "brotbrother", there will be mismatch.
			// So, I have to keep the current value of 'index' with in order not to miss the word "brother" in "brotbrother"
			if (searchingWordIndex > 0){
				index -=1;
			}
			// Also the 'searchingWordIndex' is set to 0 - the beginning of the searching word
			searchingWordIndex = 0;
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