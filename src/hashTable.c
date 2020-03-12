#include "hashTable.h"
#include "list.h"

int initHashtable(HASHTABLE **table){
	(*table) = (HASHTABLE *)malloc(sizeof(HASHTABLE));
	if ((*table) == NULL){
		printf("\nError: fail in memory allocation\n");
		return EXIT_FAILURE;
	}
	(*table)->slot = NULL;
	(*table)->slot = (LIST **)malloc(INITIAL_SLOT_LENGTH * sizeof(LIST *));
	if ((*table)->slot == NULL){
		printf("\nError: fail in memory allocation\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int computeHashvalue(char letter, char *word, int *value){
	if (word == NULL){
		printf("error: word is NULL\n");
		return EXIT_FAILURE;
	}
	int val = 0, n = 0, pow = 1, j;
	char *c = word;
	while (*c != '\0'){
		if ((*c == letter) || (*c == letter + 32) || (*c == letter - 32)){
			for (j = 0; j < n; j++){
				pow *= 2;
			}
			val += pow;
		}
		pow = 1;
		c++;
		n++;
	}
	*value = val;
	return EXIT_SUCCESS;
}

int hashFunction(LIST **words, char letter, int wordLen){
	HASHTABLE *table = NULL;
	char *word = NULL;
	int i, value, maxSize = 0, maxList = 0, maxValue = 0, slotLength = INITIAL_SLOT_LENGTH, slotCount = 0;
	word = (char *)malloc(wordLen + 1);
	if (word == NULL){
		printf("\nError: fail in memory allocation\n");
		return EXIT_FAILURE;
	}
	if (initHashtable(&table) == EXIT_FAILURE){
		return EXIT_FAILURE;
	}
	while ((*words)->head != NULL){
		pop(*words, word);
		if (computeHashvalue(letter, word, &value) == EXIT_FAILURE){
			return EXIT_FAILURE;
		}
		for (i = 0; i < slotCount; i++){
			if ((table->slot[i]->value) == value){
				insert(table->slot[i], word);
				break;
			}
		}
		if (i == slotCount){
			if (slotCount == slotLength - 1){
				slotLength *= 2;
				LIST **tmp = (LIST **)realloc(table->slot, slotLength * sizeof(LIST *));
				if (tmp == NULL){
					printf("\nError: fail in memory allocation\n");
					return EXIT_FAILURE;
				}
				table->slot = tmp;
			}
			table->slot[slotCount] = (LIST *)malloc(sizeof(LIST));
			if (table->slot[slotCount] == NULL){
				printf("\nError: fail in memory allocation\n");
				return EXIT_FAILURE;
			}
			table->slot[slotCount]->value = value;
			table->slot[slotCount]->head = NULL;
			table->slot[slotCount]->size = 0;
			insert(table->slot[slotCount], word);
			(slotCount)++;
		}
	}
	free(word);
	for (i = 0; i < slotCount; i++){
		if ((table->slot[i]->size) >= maxSize){
			if ((table->slot[i]->size) == maxSize){
				if ((table->slot[i]->value) < maxValue){
					maxSize = (table->slot[i]->size);
					maxList = i;
					maxValue = (table->slot[i]->value);
				}
			}
			else{
				maxSize = (table->slot[i]->size);
				maxList = i;
				maxValue = (table->slot[i]->value);
			}
		}
	}
	(*words)->head = table->slot[maxList]->head;
	(*words)->size = maxSize;
	for (i = 0; i < slotCount; i++){
		if (i != maxList){
			free(table->slot[i]);
		}
	}
	free(table);
	return EXIT_SUCCESS;
}
