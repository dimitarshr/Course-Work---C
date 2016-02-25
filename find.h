#pragma once
#include <stdio.h>

/* The 'searchMethod' is of type void and takes a number of arguments.
 * It takes the word I am looking for, the current line of text, the original text,
 * the number of matches, the number of the current line, the file pointer to write to and the file name to write to.
 * At the start of every line the 'numberOfMatches' which is passed as a pointer is set to 0.
 * There is a for loop that goes through the whole line of text character by character.
 * It compares every character of the line with the characters of the searching word.
 * In the 'searchMethod' there is a 'searchingWordIndex' variable which value is incremented if there is a match between the characters.
 * The 'searchingWordIndex' keep track of the number of characters that are the same.
 * If the 'searchingWordIndex' is equal to the searching word length, that means that there is a match.
 * When they are equal, I store the current 'index' of the for loop, where the last character of the searching word occures
 * For example, when I look for "brother" in "brotherhood" I will store the index of the second 'r' in "brotherhood"
 * Then I use a while loop to go back to the beginnig of the word "brotherhood".
 * Now I start printing every character until I reach I new line or a space.
 * Once I have printed everything I set the 'searchingWordIndex' to 0, as now I looking for a new match.
 * On the other hand, if there is a mismatch between the characters, we have diffent words
 * If 'searchingWordIndex' is greater than zero, that means that only part of the word matched. In order not to miss the next letter I subtract one from the 'index'.
 * For example, if I look for "brother" and I search in "brotbrother" once I reach the second 'b' of "brotbrother", there will be a mismatch.
 * So, I have to keep the current value of 'index' with in order not to miss the word "brother" in "brotbrother".
 * Also the 'searchingWordIndex' is set to 0 - the beginning of the searching word.
*/
void searchMethod(char *word, char *line, char* originalText, int *numberOfMatches,int *numberOfLine, FILE *fPointerWrite, char *writeFileName);

/* The 'ignoreCaseMethod' is of type void and takes a string and converts every letter to lower case.
 * There is a for loop that goes through the text and converts every letter to lower case using the method 'tolower'.
*/
void ignoreCaseMethod(char *word);