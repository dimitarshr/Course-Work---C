#include "find.h"
#include <stdio.h>
#include <string.h>

void searchMethod(char *word, char line[500], int *numberOfMatches, int *numberOfLine, FILE *fPointerWrite, char *writeFileName){
	int textLength = strlen(line);
	int wordLength = strlen(word);
	int posText = 0;
	int start = 0;
	*numberOfMatches = 0;
	
	for (int index=0;index<textLength;index++){
		if (word[posText] == line[index]){
			posText = posText + 1;
		
			if (posText == wordLength){
				*numberOfMatches = *numberOfMatches + 1;
				if (*numberOfMatches == 1){
					if (writeFileName == NULL)
						printf("\tFound match(es) on line %d: ",*numberOfLine);
					else
						fprintf(fPointerWrite,"\tFound match(es) on line %d: ",*numberOfLine);
				}
				start = index;
				while (line[start-1] != ' ' && start-1 >= 0)
					start = start - 1;
				while (line[start] != ' ' && line[start]!='\n' && line[start] != '\0'){
					if (writeFileName == NULL)
						printf("%c",line[start]);
					else
						fprintf(fPointerWrite, "%c",line[start]);
					start = start + 1;
				}
				if (writeFileName == NULL)
					printf(" ");
				else
					fprintf(fPointerWrite, " ");
				posText = 0;
			}
		}
		else {
			posText = 0;
		}
	}
	if (*numberOfMatches != 0 && writeFileName == NULL)
		printf("\n");
	else if (*numberOfMatches != 0 && writeFileName != NULL)
		fprintf(fPointerWrite, "\n");
}