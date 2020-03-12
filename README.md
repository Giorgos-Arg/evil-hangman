# evil-hangman

This program implements the [Evil Hangman](http://nifty.stanford.edu/2011/schwarz-evil-hangman/) game.

## Usage

Compilation

```bash
make -C ./src
```

Run

```bash
./src/evilHangman <word_file>
```

Where <word_file> is a text file containing the word length at the top of the file and then a list words with the same 
length.

## Example

```bash
./src/evilHangman data/length3.txt

***********************************************************
***             Welcome to (Evil) Hangman               ***
                        ________
                        |/      |
                        |      (_)
                        |      \|/
                        |       |
                        |      / \
                        |
                        |
***     You are going to play against the computer      ***
***********************************************************


Type the number of total guesses: 3


----------------------
Words possible: 1294
Progress: _ _ _
Number of Guesses: 3
----------------------

Guess a letter:a
a is not in the word!


----------------------
Words possible: 867
Progress: _ _ _
Number of Guesses: 2
----------------------

Guess a letter:o
o is not in the word!


----------------------
Words possible: 579
Progress: _ _ _
Number of Guesses: 1
----------------------

Guess a letter:e
e is not in the word!

**************************************************
You run out of guesses. You lost!
The secret word is: nit
```

## Author

Giorgos Argyrides (g.aryrides@outlook.com)
