#ifndef HANGMAN_H_
#define HANGMAN_H_

#include "list.h"
#include "hashTable.h"
#include <time.h>

/** 
 * Reads a list of words and the word length from a text file.
 * 
 *  @param words the list of the words.
 *  @param filePath the file path
 *  @param wordLen the length of the word.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int readFile(LIST **words, char *filePath, int *wordLen);

/** 
 *  Allows the user can play the Evil hangman game by following the rules of the game. The user inputs the number of 
 *  total guesses and then she/he starts guessing the letters of the word. The program keeps asking the user to type a 
 *  letter until he finds the word or until she/he runs out of guesses. It prints the appropriate error messages if the 
 *  user gives invalid input.
 * 
 *  @param words the list of the words.
 *  @param wordLen the length of the word.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int play(LIST **words, int wordLen);

/** 
 *	Checks if the game is solved and prints the appropriate messages.
 *
 *  @param listHead the head of the word list
 *  @param progress a string with the progress the user made in finding the word
 *  @param size the size of the word list
 *  @param solved 1 if the game is solve, 0 if the game is not solved
 **/
void checkIfSolved(NODE *listHead, char *progress, int size, int solved);

#endif /* HANGMAN_H_ */
