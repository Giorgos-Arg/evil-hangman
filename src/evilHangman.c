/* 
 * This program implements the Evil hangman game.
 *  
 * Given a list of words, the length of the word and the number of tries it asks the user to play. The player tries to 
 * find the word that the computer chose from the list by guessing the letters one-by-one. Every time the user guesses a
 * letter correctly, the computer prints all the appearances of that letter in the word. If the player guesses all the 
 * letters correctly before running out of tries, then the player wins the game.
 * 
 * In Evil hangman, the computer delays picking a word until it is forced to. As a result, the computer is always 
 * considering a set of words that could be the answer. In order to fool the user into thinking it is playing fairly,
 * the computer only considers words with the same letter pattern. In this program the upper-case and lower-case letters 
 * are treated as equal.
 *
 *  @author Giorgos Argyrides
 * 
 */

#include "evilHangman.h"

int readFile(LIST **words, char *filePath, int *wordLen){
	char word[MAX_LINE_LENGTH];
	FILE *fp = NULL;
	if ((fp = fopen(filePath, "r")) == NULL){
		printf("\nError: Unable to open %s\n", filePath);
		return EXIT_FAILURE;
	}
	if (initList(words) == EXIT_FAILURE){
		return EXIT_FAILURE;
	}
	if (fscanf(fp, "%d", wordLen) != 1){
		printf("\nError: invalid input for the word length in the file %s\n", filePath);
		return EXIT_FAILURE;
	}
	fgetc(fp); //get the \n character
	while (fgets(word, MAX_LINE_LENGTH, fp) != NULL){
		if (word[*wordLen] == '\n'){
			word[*wordLen] = '\0';
		}
		if (insert(*words, word) == EXIT_FAILURE){
			printf("\nError inserting the word in the list.\n");
			return EXIT_FAILURE;
		}
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int play(LIST **words, int wordLen){
	int i, j, guesses = 0, solved = 0, lettersGiven = 0;
	char *progress, letterArray[52];
	char letter;
	progress = (char *)malloc(wordLen + 1);
	if (progress == NULL){
		printf("\nError: fail in memory allocation.\n");
	}
	//initialize progress
	for (i = 0; i < wordLen; i++){
		progress[i] = '_';
	}
	progress[wordLen] = '\0';
	printf("\n***********************************************************"
			"\n***\t\tWelcome to (Evil) Hangman\t\t***"
			"\n\t\t\t________"
			"\n\t\t\t|/      |"
			"\n\t\t\t|      (_)"
			"\n\t\t\t|      \\|/"
			"\n\t\t\t|       |"
			"\n\t\t\t|      / \\"
			"\n\t\t\t|"
			"\n\t\t\t|"
			"\n***\tYou are going to play against the computer\t***"
			"\n***********************************************************\n");
	printf("\n\nType the number of total guesses: ");
	while (scanf("%d", &guesses) != 1 || guesses <= 0){
		printf("\nError:invalid input, please type an integer > 0!");
		printf("\n\nType the number of total guesses: ");
		while (getchar() != '\n');
	}
	while (solved == 0 && guesses > 0){
		printf("\n\n----------------------\nWords possible: %d", (*words)->size);
		printf("\nProgress: ");
		for(i = 0; i < wordLen; i++){
			printf("%c ", progress[i]);
		}
		printf("\nNumber of Guesses: %d", guesses);
		printf("\n----------------------\n");
		printf("\nGuess a letter:");
		while (getchar() != '\n'); //clear the buffer
		while (scanf("%c", &letter) != 1 || ((letter < 'a' || letter > 'z') && (letter < 'A' || letter > 'Z'))){
			printf("\nPlease type a valid letter (a-z) or (A-Z)!\n\n");
		}
		//check if letter was already given
		for (j = 0; j < lettersGiven; j++){
			if (letterArray[j] == letter || (letterArray[j] == letter + 32) || (letterArray[j] == letter - 32))
				break;
		}
		if (j < lettersGiven){
			printf("\nLetter %c was already given!\n", letter);
			continue;
		}
		else{
			letterArray[lettersGiven] = letter;
			lettersGiven++;
		}
		if (hashFunction(words, letter, wordLen) == EXIT_FAILURE){
			return EXIT_FAILURE;
		}
		for (i = 0; i < wordLen; i++){
			if ((*words)->head->name[i] == letter || ((*words)->head->name[i] == letter + 32) || 
				((*words)->head->name[i] == letter - 32)){
				progress[i] = letter;
			}
		}
		solved = 1;
		for (i = 0; i < wordLen; i++){
			if (progress[i] == '_'){
				solved = 0;
				break;
			}
		}
		for (i = 0; i < wordLen; i++){
			if ((progress[i] == letter) || (progress[i] == letter + 32) || (progress[i] == letter - 32)){
				printf("%c is in the word!\n", letter);
				break;
			}
		}
		if (i == wordLen){
			printf("%c is not in the word!\n", letter);
			guesses--;
		}
	}
	checkIfSolved((*words)->head, progress, (*words)->size, solved);
	return EXIT_SUCCESS;
}

void checkIfSolved(NODE *listHead, char *progress, int size, int solved){
	int randomIndex, i = 0;
	NODE *p = listHead;
	if (solved == 1){
		printf("\n**************************************************\n");
		printf("Congratulations, you win the game!\nThe secret word is: %s ", progress);
		printf("\n**************************************************\n");
	}
	else{
		srand(time(NULL));
		randomIndex = rand() % size;
		while (((p->next) != NULL) && (i < randomIndex)){
			p = p->next;
			i++;
		}
		printf("\n**************************************************\n");
		printf("You run out of guesses. You lost!\nThe secret word is: %s ", p->name);
		printf("\n**************************************************\n");
	}
}

int main(int argc, char **argv){
	LIST *words = NULL;
	int wordLen;
	if (argc != 2){
		printf("\nError: invalid arguments\nplease type the arguments in this syntax:\n ./hangMan words.txt\n");
		exit(EXIT_FAILURE);
	}
	if (readFile(&words, argv[1], &wordLen) == EXIT_FAILURE){
		exit(EXIT_FAILURE);
	}
	if (play(&words, wordLen) == EXIT_FAILURE){
		exit(EXIT_FAILURE);
	}
	return 0;
}
