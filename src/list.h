#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s{
	char *name;
	struct node_s *next;
} NODE;

typedef struct list_s{
	NODE *head;
	int size;
	int value;
} LIST;

/** 
 *  Initializes the list with size = 0,value = 0 and the head points to NULL.
 *
 *  @param l the list to be initialized.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int initList(LIST **l);

/** 
 *  Inserts a word in the list.
 *
 *  @param l the word list.
 *  @param c the word to be inserted in the list.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int insert(LIST *l, char *c);

/** 
 *  Removes a word from the list.
 *
 *  @param l the word list.
 *  @param c the word to be taken out from the list.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
int pop(LIST *l, char *retval);

/** 
 *  Prints a list of words.
 *
 *  @param l the word list.
 *  @return returns EXIT_SUCCESS if the function completes without errors.
 **/
void printList(LIST *l);

#endif /* LIST_H_ */
