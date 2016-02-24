#include "find.h"
#include <stdio.h>

int main(int argc, char** argv){
	char* searchingWord = NULL;
	char* readFileName = NULL;
	char* writeFileName = NULL;
	char* originalText = NULL;
	char* singleLine = NULL;
	char singleLetter;
	FILE *fPointerRead = stdin;
	FILE *fPointerWrite = stdout;
	int numberOfLine = 0;
	int noMatchFlag = 0;
	int numberOfMatches = 0;
	int ignoreCase = 0;
	int numberOfChars = 0;
	
	// This for loop goes through the command line arguments and stores the appropriate values in different variables
	// The argument after '-i' is the name of the input file we are using and
	// The argument after '-o' is the name of the output file we are using
	// The argument '-c' means that I have to ignore the upper and/or the lower case of the text I am searching in
	for (int i = 1;i<argc;i++){
		// If the current argument is not '-i','-o' or '-c' 
		// and the argument in front of it is not '-i','-o' that means that this is the word I have to look for.
		if (strcmp(argv[i], "-i") != 0 && strcmp(argv[i], "-o") != 0 && strcmp(argv[i], "-c") != 0 && strcmp(argv[i-1], "-i") != 0 && strcmp(argv[i-1], "-o") != 0){
			searchingWord = argv[i];
		}
		// If the current argument is '-i' and there are more arguments after this, that means that this is the input file.
		// In case the user decides not to enter input file, I am assuming that he/she wants to use the standard input in order to get the text to search in
		// If the user enters invalid file name, the program stops
		else if (strcmp(argv[i],"-i") == 0){
			if ((i+1)<argc){
				readFileName = argv[i+1];
				fPointerRead = fopen(readFileName, "r");
				if (fPointerRead == NULL){
					printf("\n\tThe input file is invalid!\n");
					return 0;
				}
			}
			else {
				printf("\n\tYou did not provide input file!\n");
				return 0;
			}
		}
		// If the current argument is '-o' that means that this is the output file.
		// In case the user decides not to enter output file, I am assuming that he/she wants to use the standard output in order to output the results from the search
		// If the user enters invalid file name, the program stops
		else if (strcmp(argv[i], "-o") == 0){
			if ((i+1)<argc){
				writeFileName = argv[i+1];
				fPointerWrite = fopen(writeFileName, "w");
			}
			else{
				printf("\n\tYou did not provide output file!\n");
				return 0;
			}
		} 
		// If the current argument is '-c', that means that we have to ignore the case of the letters. So we raise the 'ignoreCase' flag
		else if (strcmp(argv[i], "-c") == 0){
			ignoreCase = 1;
		}
	}
	
	// If the user did not input anything for the searching word the program stops and displays a message as otherwise it would crash
	if (searchingWord == NULL){
		printf("\n\tYou did not enter the word to search for!\n");
		return 0;
	}
	
	// If the user did not provide input file this part of code is executed
	// By default the 'fPointerRead' value is equal to the standard input
	if (fPointerRead == stdin){
		int reallocateIndex = 1;
		// At the start I allocate memory for 500 characters
		singleLine = (char*)malloc(sizeof(char)*500);
		originalText = (char*)malloc(sizeof(char)*500);
		// This while loop goes through the whole standard input character by character
		while ((singleLetter = fgetc(fPointerRead)) != EOF){
			// If we have more charactes than the allocated memory, we reallocate more memory 
			if(numberOfChars == (reallocateIndex*500)){
				reallocateIndex += 1;
				singleLine = (char*)realloc(singleLine,reallocateIndex*500);
				originalText = (char*)realloc(originalText,reallocateIndex*500);
			}
			// Here I store every read character in the 'singleLine' pointer
			singleLine[numberOfChars] = singleLetter;
			numberOfChars += 1;
			// When I reach the end of the line this code is executed
			if (singleLetter == '\n'){
				numberOfLine += 1;
				// As I have read until the new line character I have to implicitly add the null terminator
				singleLine[strlen(singleLine)] = '\0';
				// If I have the 'ignoreCase' flag raised, I have to convert all letters to lower case in order to compare them
				// Before I convert the text to lower case, I store it in the variable 'originalText'
				// This allowes me to print the text as it is in the original form
				strcpy(originalText,singleLine);
				// If the 'ignoreCase' flag is raised I convert everything to lower case with the function 'ignoreCaseMethod'
				if (ignoreCase == 1){
					ignoreCaseMethod(singleLine);
					ignoreCaseMethod(searchingWord);
				}
				
				// Once I have everything I call the 'searchMethod' function, which is of type void
				searchMethod(searchingWord, singleLine, originalText, &numberOfMatches, &numberOfLine, fPointerWrite, writeFileName);
				// As I am passing the variable 'numberOfMatches' by pointer, once the method is executed I know if there were some matches
				// If there were no matches on this line, I increment the 'noMatchFlag' by one
				if (numberOfMatches == 0)
					noMatchFlag += 1;	
				numberOfChars = 0;
			}
		}
		// As I have allocated some memory, I am freeing it here.
		free(singleLine);
		free(originalText);
	}

	else{
		int maxLineLength = 0;
		// This while loop goes through the whole file character by character and calculates the length of the longest line
		while ((singleLetter = fgetc(fPointerRead)) != EOF){
			numberOfChars = numberOfChars + 1;
			if (numberOfChars > maxLineLength){
				maxLineLength = numberOfChars;
			}
			if (singleLetter == '\n'){
				numberOfChars = 0;
			}
		}
		// As I have already read the whole file with fgetc I have to go to the beginning of the file again
		fseek(fPointerRead,0,SEEK_SET);
		// I allocate memory that is capable to read the longest line in the file
		singleLine = (char*)malloc(sizeof(char)*(maxLineLength+1));
		originalText = (char*)malloc(sizeof(char)*(maxLineLength+1));
		// If the file is not empty, maxLineLength is not equal to 0, I read the file line by line
		if (maxLineLength > 0){
			while((fgets(singleLine,sizeof(char)*(maxLineLength+1),fPointerRead)) != NULL){
				numberOfLine += 1;
				// As I have read until the new line character I have to implicitly add the null terminator
				singleLine[strlen(singleLine)] = '\0';
				// If I have the 'ignoreCase' flag raised, I have to convert all letters to lower case in order to compare them
				// Before I convert the text to lower case, I store it in the variable 'originalText'
				// This allowes me to print the text as it is in the original form
				strcpy(originalText,singleLine);
				// If the ignore case flag is raised I convert everything to lower case
				if (ignoreCase == 1){
					ignoreCaseMethod(singleLine);
					ignoreCaseMethod(searchingWord);
				}
				// Once I have everything I call the 'searchMethod' function, which is of type void
				searchMethod(searchingWord, singleLine, originalText, &numberOfMatches, &numberOfLine, fPointerWrite, writeFileName);
				// As I am passing the variable 'numberOfMatches' by pointer, once the method is executed I know if the were some matches
				// If there were not any matches on this line, I increment the 'noMatchFlag' by one
				if (numberOfMatches == 0)
						noMatchFlag = noMatchFlag + 1;
			}
		}
		// As I have allocated some memory, I am freeing it here.
		free(singleLine);
		// Once I have finished reading the input file, I close the file pointer.
		fclose(fPointerRead);
	}
	// After I have finished reading the text either from the standart input or from a file
	// I check if the number of 'noMatchFlag' is equal to the number of lines
	// If so, that means that we did not have any matches
	if (noMatchFlag == numberOfLine)
		fprintf(fPointerWrite,"No match was found!");
	// Once I have finished writing to the output file, I close the file pointer.
	if (fPointerWrite != stdout)
		fclose(fPointerWrite);
	
	return 0;
}