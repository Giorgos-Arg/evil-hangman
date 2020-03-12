#include "list.h"

int initList(LIST **l){
	*l = (LIST *)malloc(sizeof(LIST));
	if ((*l) == NULL){
		printf("\nError: fail in memory allocation\n");
		return EXIT_FAILURE;
	}
	(*l)->head = NULL;
	(*l)->size = 0;
	(*l)->value = 0;
	return EXIT_SUCCESS;
}

int insert(LIST *l, char *c){
	NODE *p = NULL;
	if (l == NULL){
		printf("\nerror: list is NULL\n");
		return EXIT_FAILURE;
	}
	p = (NODE *)malloc(sizeof(NODE));
	if (p == NULL){
		printf("\nError: fail in memory allocation\n");
		return EXIT_FAILURE;
	}
	p->name = (char *)malloc(strlen(c) + 1);
	if (p->name == NULL){
		printf("\nError: fail in memory allocation\n");
		return EXIT_FAILURE;
	}
	strcpy(p->name, c);
	p->next = l->head;
	l->head = p;
	(l->size)++;
	return EXIT_SUCCESS;
}

int pop(LIST *l, char *retval){
	NODE *p = NULL;
	if ((l == NULL) || (l->head == NULL) || (l->size == 0)){
		printf("List is empty\n");
		return EXIT_FAILURE;
	}
	if (retval == NULL){
		printf("Retval is NULL\n");
		return EXIT_FAILURE;
	}
	p = l->head;
	strcpy(retval, p->name);
	l->head = p->next;
	(l->size)--;
	free(p);
	return EXIT_SUCCESS;
}

void printList(LIST *l){
	NODE *p = NULL;
	if ((l == NULL) || (l->head == NULL) || (l->size == 0)){
		printf("The list is empty\n");
		return;
	}
	p = l->head;
	while (p != NULL){
		printf("%s, ", p->name);
		p = p->next;
	}
	printf("\n");
}

#ifdef DEBUG

static void tester()
{
	LIST *list = NULL;
	char word[10];
	initList(&list);
	printList(list);
	insert(list, "abc");
	insert(list, "def");
	printList(list);
	pop(list, word);
	printf("word: %s\n", word);
	printList(list);
}

int main()
{
	tester();
	return 0;
}

#endif
