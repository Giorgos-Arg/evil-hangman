#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "list.h"

#define INITIAL_SLOT_LENGTH 2
#define MAX_LINE_LENGTH 100

typedef struct
{
	LIST **slot;
} HASHTABLE;

/** 
 *  Initializes a table of lists.
 *
 *  @param table the hashtable to be initialized
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int initHashtable(HASHTABLE **table);

/** 
 *  Computes an integer value for a word so it can be categorized based on the number of appearances of the letter and 
 *  its places in the word.
 *
 *  @param letter the base on which the value will be computed.
 *  @param word the word that will be turned into an integer value.
 *  @param value an integer value of a word basing on a letter.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int computeHashvalue(char letter, char *word, int *value);

/** 
 *  Categorizes the original word list into other lists according to the user's input letter and then chooses 
 *  the list with the maximum number of words as the new word list.
 *
 *  @param words the list of the words.
 *  @param letter the user's input letter.
 *  @param wordLen the length of the word.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int hashFunction(LIST **words, char letter, int wordLen);

#endif /* HASHTABLE_H_ */
