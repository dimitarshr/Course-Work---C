#pragma once
#include <stdio.h>

void searchMethod(char *word, char *line, char* originalText, int *numberOfMatches,int *numberOfLine, FILE *fPointerWrite, char *writeFileName);
void ignoreCaseMethod(char *word);