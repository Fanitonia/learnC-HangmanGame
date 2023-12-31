/*
A basic hangman game.
Created by Fanitonia for learning C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

void chooseWord();
void printScreen();
void getLetter();
void checkLetter();
void checkWord();
void checkLose();
void resetGame();

char words[][15] = {"COMPUTER", "KEYBOARD", "HEADPHONE", "MIRROR", "WATER", "WHITE", "PUZZLE", "SOCCER", 
                    "BASKETBALL", "BREAKFAST", "ELECTRICITY", "HORROR", "PAPER", "MOTHERBOARD", "BEER"};
char hints[][20] = {"TECHNOLOGY", "COMPUTERS", "SOUND", "LIGHT", "A DRINK", "A COLOR", "HANGMAN GAME", "A SPORT",
                    "A SPORT", "MORNING", "NIKOLA TESLA", "A MOVIE GENRE", "WHITE", "COMPUTERS", "A DRINK"};
char word[10];
char wordOnScreen[10];
char letter;
char letters[6];
char guessWord[10];
char restart = 'N';
int wordNumber;
int numberOfWords;
int len;
int wrongGuess = 0;
int correctLetters = 0;
int winTrack = 0;
int loseTrack = 0;
int hintNumber = 3;
bool win = false;
bool lose = false;
bool usedCorrectLetter = false;
bool hintOpen = false;
bool hintUsed = false;

int main()
{   
    do
    {   
        system("cls");
        chooseWord();
        for(int i = 0; i<=len; i++)
        {
            wordOnScreen[i] = '_';
        }

        do{
            printScreen();
            getLetter();
            checkLetter(); 
            checkLose();
            system("cls"); 
        }while(win == false && lose == false);

        printScreen();
        printf("\nWant to play again? (Y/N) ");
        restart = getch();
        restart = toupper(restart);
        resetGame();
        
    }while(restart == 'Y');

    printf("\nPress a button for closing the game.");
    getch();
}

void chooseWord()
{
    numberOfWords = sizeof(words)/sizeof(words[0]); 
    srand(time(0));
    wordNumber = rand() % numberOfWords;
    strcpy(word, words[wordNumber]);
    len = strlen(word);
}

void printScreen()
{   
    if(win == true)
    {
        winTrack++;
    }
    else if(lose == true)
    {
        loseTrack++;
    }
    printf("\n\t");

    for(int j = 0; j<len; j++)
    {
        printf("%c ", wordOnScreen[j]);
    }

    printf("\n\t\t\t______");
    printf("\t\tWins: %d", winTrack);
    printf("\tLoses: %d", loseTrack);
    printf("\n\t\t\t|    |");
    printf("\t\tNumber of hints you have: %d (press '+' for hint)\n", hintNumber);
  
    if(wrongGuess > 0)
        printf("\t\t\t|    O");
    else
        printf("\t\t\t|");

    if(hintOpen == true)
    {
        printf("\t\tHint: %s\n", hints[wordNumber]);     
    }
    else if(hintUsed == true)
    {
        printf("\t\tYou can't take hints anymore!\n");
    }
    else
        printf("\n");
  
    if(wrongGuess == 1 || wrongGuess == 0)
        printf("\t\t\t| \n");
    if(wrongGuess == 2)
        printf("\t\t\t|    |\n");
    if(wrongGuess == 3)
        printf("\t\t\t|    |\\ \n");
    if(wrongGuess > 3)
        printf("\t\t\t|   /|\\ \n");
    if(wrongGuess > 4)
        printf("\t\t\t|    ^ \n");
    else
        printf("\t\t\t|\n");
    if(win == false && lose == false)
    {
        printf("The letters that you already tried: ");
        for(int h = 0; h<wrongGuess; h++)
        {
            printf("%c ", letters[h]);
        }
        printf("\nIf you want to guess the word press '*'");
    }
    else if(win == true)
    {
        printf("You guessed it correct! You are a life saver!");    
    }
    else if(lose == true)
    {
        printf("He died unfortunately. You lose the game :(");   
    }
}   

void getLetter()
{
    printf("\nGuess a letter: ");
    scanf(" %c", &letter);
    letter = toupper(letter);
}

void checkLetter()
{
    bool used = false;
    int letterOfWord = len;

    if(letter == '*')
    {
        checkWord();
    }
    else if(letter == '+')
    {
        if(hintNumber != 0)
        {
            hintOpen = true;
            hintNumber--;
        }
        else
        {
            hintUsed = true;
        }
    }
    else
    {
        for(int m = 0; m<len; m++)
        {
            if(wordOnScreen[m] == letter)
            {
                usedCorrectLetter = true;
            }
        }

        for(int m = 0; m<len; m++)
        {
            if(word[m] == letter)
            {
                wordOnScreen[m] = letter;
                if(usedCorrectLetter == false)
                {
                    correctLetters++;
                    usedCorrectLetter = false;
                }               
            }
            else
            {
                letterOfWord--;
            }
        }
        if(correctLetters == len)
        {
            win = true;
        }
        if(letterOfWord == 0)
        {
            for (int i = 0; i<5; i++)
            {
                if(letters[i] == letter)
                {
                    used = true;
                    break;
                }   
            }
            if(used == false)
            {
                letters[wrongGuess] = letter;
                wrongGuess++;
            }
        }
    }      
}

void checkWord()
{
    printf("What is your guess? ");
    scanf("%s", guessWord);
    strcpy(guessWord ,strupr(guessWord));

    if(strcmp(word, guessWord) == 0)
    {
        strcpy(wordOnScreen, word);
        win = true;
    }
    else
    {
        wrongGuess++;
    }  
}

void checkLose()
{
    if(wrongGuess == 5)
    {
        strcpy(wordOnScreen, word);
        lose = true;
    }
}

void resetGame()
{
    win = false;
    lose = false; 
    wrongGuess = 0; 
    strcpy(letters, "     ");
    correctLetters = 0; 
    hintOpen = false;
    hintUsed = false;
}


