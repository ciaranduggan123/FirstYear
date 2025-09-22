/*
Description: Program for a word guessing game.
    Prompt the user to guess the characters in the word “coding”.
    Provide feedback on whether each guessed character entered is present or not. 
    The user is allowed a maximum of 7 wrong character guesses.
Name: Ciaran Duggan
Student ID: C23380123
Date: 9/4/24
*/

#include <stdio.h>
#include <string.h>

#define SIZE 7

//Function signature
int checkGuess(char[], char);

int main()
{
    char word[SIZE] = "coding";
    char guessedWord[SIZE];
    int wrongAttempts = SIZE;
    int i;
    char guess;

    //Putting underscores into each spot inside the guessedWord array
    for (i = 0; i < strlen(word); i++)
    {
        guessedWord[i] = '_';
    } //end for loop

    //Placing the NULL character in the last place of the guessedWord array
    guessedWord[strlen(word)] = '\0';

    printf("Guess the word game.\n");

    //user has 7 incorrect guesses
    while (wrongAttempts > 0)
    {
        printf("\nEnter your guess (single character): ");
        scanf("%c", &guess);

        //clear input buffer
        while(getchar() != '\n');

        //call function checkGuess() to check if the guessed character is in the word
        if (checkGuess(word, guess) == 1)
        {
            //add correctly guessed characters into the guessedWord array
            for (i = 0; i < strlen(word); i++)
            {
                if (word[i] == guess)
                {
                    guessedWord[i] = guess;
                }//end if 
            }//end for loop

            printf("\n%c is correct. It is located here: %s\n", guess, guessedWord);

            //if the user correctly guesses the word, break out of the while loop and end the program
            if(strcmp(word, guessedWord) == 0)
            {
                printf("\nYou win. You guessed the word: %s\n", word);

                //exit the loop and end the program
                break;
            }//end if
        }//end if

        else //if the user incorrectly guesses a character in the word
        {
            printf("%c is not in the word.\n", guess);

            //wrong attempts taken away
            wrongAttempts--;

            printf("Attempts remaining: %d\n", wrongAttempts);

            //if all attempts used end program
            if (wrongAttempts == 0)
            {
                printf("\nGame over, you have run out of attempts. The correct word was: %s\n", word);

                break;
            }//end if
        }//end else
    }//end while

    return 0;
}//end main

int checkGuess(char word[], char guess) //function to check if guess is correct or incorrect
{
    int len = 0;
    int i;

    //get the length of the word
    len = strlen(word);

    for (i = 0; i < len; i++)
    {
        //if the guessed character is in the word
        if (word[i] == guess)
        {
            //exit the function and return 1
            return 1;
        }//end if
    }//end for loop

    // return 0 if the guessed character is NOT in the word
    return 0;
}//end checkguess