#include "find.h"
#include <stdio.h>

int main(int argc, char** argv){
	char* searchingWord = NULL;
	char* readFileName = NULL;
	char* writeFileName = NULL;
	FILE *fPointerRead;
	FILE *fPointerWrite;
	int numberOfLine = 0;
	int noMatchFlag = 0;
	int numberOfMatches = 0;
	int ignoreCase = 0;
	int size = 0;
	int count = 0;
	char singleLetter;

	for (int i = 0;i<argc;i++){
		if (strcmp(argv[i], "find") != 0 && strcmp(argv[i], "-i") != 0 && strcmp(argv[i], "-o") != 0 && strcmp(argv[i], "-c") != 0 && strcmp(argv[i-1], "-i") != 0 && strcmp(argv[i-1], "-o") != 0){
			searchingWord = argv[i];
		}
		else if (strcmp(argv[i],"-i") == 0 && (i+1)<argc && strcmp(argv[i+1],"-o") != 0 && strcmp(argv[i+1],"-c") != 0){
			readFileName = argv[i+1];
			fPointerRead = fopen(readFileName, "r");
			if (fPointerRead == NULL){
				cprintf("\n\tThe input file is invalid!\n");
				return 0;
			}
		}
		else if (strcmp(argv[i], "-o") == 0 && (i+1)<argc && strcmp(argv[i+1],"-i") != 0 && strcmp(argv[i+1], "-c") != 0){
			writeFileName = argv[i+1];
			fPointerWrite = fopen(writeFileName, "w");
		}
		else if (strcmp(argv[i], "-c") == 0){
			ignoreCase = 1;
		}
	}
	if (searchingWord == NULL){
		printf("\n\tYou did not enter the word to search for!\n");
		return 0;
	}
	if (readFileName != NULL){
		
		while ((singleLetter = fgetc(fPointerRead)) != EOF){
			count = count + 1;
			if (count > size){
				size = count;
			}
			if (singleLetter == '\n'){
				count = 0;
			}
		}
		fseek(fPointerRead,0,SEEK_SET);
		
		char *singleLine = (char*)malloc(sizeof(char)*size);
		
		while((fgets(singleLine,sizeof(char)*size,fPointerRead)) != NULL){
			numberOfLine = numberOfLine + 1;
			if (ignoreCase == 1){
				strlwr(singleLine);
				strlwr(searchingWord);
			}
			if (writeFileName == NULL){
				searchMethod(searchingWord, singleLine, &numberOfMatches, &numberOfLine, fPointerWrite, writeFileName);
			}
			else if (writeFileName != NULL){
				searchMethod(searchingWord, singleLine, &numberOfMatches, &numberOfLine, fPointerWrite, writeFileName);	
			}
			if (numberOfMatches == 0)
					noMatchFlag = noMatchFlag + 1;
		}
		free(singleLine);
		
		fclose(fPointerRead);
	}
	else{
		printf("Please enter the text: ");
		//char singleLine[1000];
		
		int size = 0;
		char *singleLine = NULL;
		int index = 0;
		char ch = 1;
		
		while((singleLetter = getc(stdin)) != '\n'){
			//singleLetter = getc(stdin);
			//if (singleLetter == '\n')
			//	singleLetter = 0;
			size = size+ 1;
			singleLine = (char*)realloc(singleLine,size);
			singleLine[index] = singleLetter;
			index = index + 1;
		}

		//printf("\n%d %c ",strlen(singleLine)-1,singleLine[strlen(singleLine)-1]);		
		//singleLine = (char*)realloc(singleLine,size+1);
		printf("%d %c ",strlen(singleLine)-1,singleLine[strlen(singleLine)-1]);
		singleLine[strlen(singleLine)-1] = '\0';
		printf("\n%d %c ",strlen(singleLine)-1,singleLine[strlen(singleLine)-1]);
		
		printf("%d",size);
		printf("%s",singleLine);
		if (index == 0){
			printf("You did not input any text!");
			return 0;
		}

		//fgets(singleLine,1000,stdin);
		numberOfLine = numberOfLine + 1;
		if (ignoreCase == 1){
			strlwr(singleLine);
			strlwr(searchingWord);
		}
		if (writeFileName == NULL){
			searchMethod(searchingWord, singleLine, &numberOfMatches, &numberOfLine, fPointerWrite, writeFileName);
		}
		else if (writeFileName != NULL){
			searchMethod(searchingWord, singleLine, &numberOfMatches, &numberOfLine, fPointerWrite, writeFileName);
		}
		if (numberOfMatches == 0)
			noMatchFlag = noMatchFlag + 1;		
		
		//free(singleLine);
	}
		
	if (noMatchFlag == numberOfLine && writeFileName == NULL)
		printf("\nNo match was found!\n");
	else if (noMatchFlag == numberOfLine && writeFileName != NULL)
		fprintf(fPointerWrite,"No match was found!");
		
	if (writeFileName != NULL)
		fclose(fPointerWrite);
	
	return 0;
}
