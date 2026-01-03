#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define WORD_LENGTH 5
#define GUESSES 6

void printWelcomeMessage(void);
int validateCommandLineArgs(int argc, char *argv[]);
char *extractAnswer(char *argv[]);
char *validateAnswer(char *answer);
char *getGuess();
bool validateGuessLength(char *guess);
void printGuess(char *guess);

int gameLoop(char *answer, int guesses);

int main(int argc, char *argv[])
{
    int guesses = GUESSES;
    int result = validateCommandLineArgs(argc, argv);
    if (result != 0)
    {
        return -1;
    }

    char *answer = extractAnswer(argv);
    // printf("%s\n", answer);
    printWelcomeMessage();

    int done = gameLoop(answer, guesses);
    if (done == 0)
    {
        printf("Congratulations, you got it!\n");
    }
    else if (done == -1)
    {
        return 0;
    }
    else
    {
        printf("Sorry, you ran out of tries\n");
    }

    free(answer);
    answer = NULL;
    return 0;
}

void printWelcomeMessage(void)
{
    printf("\n");
    printf("==========================\n");
    printf("= Welcome to fake Wordle =\n");
    printf("==========================\n");
    printf("\n");
}

int validateCommandLineArgs(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Wrong num of arguments in command line - must be 2\n");
        return -1;
    }
    char *wordptr = argv[1];
    int i = 0;
    int letters = 0;
    while (wordptr[i] != '\0')
    {
        letters++;
        i++;
    }
    if (letters != 5)
    {
        printf("Wordle only allows 5 letter words as the target word to be guessed\n");
        return -1;
    }
    return 0;
}

char *extractAnswer(char *argv[])
{
    char *word_ptr = argv[1];
    char *answer = malloc((WORD_LENGTH + 1) * sizeof(char));
    if (answer == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        answer[i] = word_ptr[i];
    }
    answer[WORD_LENGTH] = '\0';
    answer = validateAnswer(answer);
    if (answer == NULL)
    {
        printf("Error: please make sure the answer is all alphabetical!\n");
    }

    return answer;
}

char *validateAnswer(char *answer)
{
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        if (!isalpha(answer[i]))
        {
            return NULL;
        }
        answer[i] = toupper(answer[i]);
    }
    return answer;
}

char *getGuess()
{
    int c;
    int letters = 5;
    int count = 0;
    char *guess = malloc(letters * sizeof(char));
    while ((c = getchar()) != '\n' && c != EOF)
    {

        if (count > letters)
        {
            char *temp = realloc(guess, sizeof(char) * 2);
            if (temp == NULL)
            {
                printf("Memory allocation failed\n");
                return NULL;
            }
            letters *= 2;
        }
        guess[count] = toupper((char)c);
        count++;
    }
    guess[count++] = '\0';
    return guess;
}

bool validateGuessLength(char *guess)
{
    int length = strlen(guess);
    if (length != 5)
    {
        return false;
    }
    return true;
}

int gameLoop(char *answer, int guesses)
{
    printf("answer: %s\n", answer);
    bool valid_guess = false;
    do
    {
        printf("Enter your guess: \n");
        char *guess = getGuess();
        if (strcmp(guess, "QUIT") == 0)
        {
            return -1;
        }
        valid_guess = validateGuessLength(guess);
        if (valid_guess)
        {
            guesses--;
            printGuess(guess);
            // printf("your guess: %s\n", guess);
        }
        else
        {
            printf("Your guess can only be 5 characters long\n");
        }
        if (strcmp(guess, answer) == 0)
        {
            return 0;
        }
        printf("Number of guesses remaining: %d\n", guesses);
    } while (!valid_guess || guesses > 0);
    return -2;
}

void printGuess(char *guess)
{
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        printf("%c", guess[i]);
        if (i < WORD_LENGTH - 1)
        {
            printf(" ");
        }
    }
    printf("\n");
}
