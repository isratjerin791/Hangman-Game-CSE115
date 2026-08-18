//Raiana Tabassum Roza--------
#include <stdio.h>   // for printf, scanf, fopen, fgets, fprintf, etc. (input/output)
#include <stdlib.h>  // for exit(), rand(), srand()
#include <string.h>  // for strcpy, strcmp, strlen, strcspn (string handling)
#include <ctype.h>   // for tolower() (converting characters to lowercase)
#include <time.h>    // for time() (used to seed the random number generator)
 
#ifdef _WIN32
#include <windows.h> // only included on Windows, needed for SetConsoleOutputCP
#endif
 
// ===================== Constants =====================
// #define creates a constant value that gets swapped in everywhere it's used
// before the code is compiled. Using names instead of raw numbers makes the
// code easier to read and easier to change later (change it in one place).
#define MAX_WORD_LENGTH 50        // longest a single word or hint string can be
#define MAX_ATTEMPTS 6            // how many wrong guesses are allowed before losing
#define MAX_WORDS_PER_CATEGORY 20 // how many words fit inside one category
 
// ===================== Structs =====================
// A struct groups several related variables together under one name.
 
// Category holds everything about one topic (e.g. "Technology"):
// its name, the list of words in it, the matching hints, and how
// many words are actually filled in.
typedef struct {
    char name[30];                                          // category title, e.g. "CSE"
    char words[MAX_WORDS_PER_CATEGORY][MAX_WORD_LENGTH];     // 2D array: up to 20 words, each up to 50 chars
    char hints[MAX_WORDS_PER_CATEGORY][MAX_WORD_LENGTH];     // matching hint for each word (same index)
    int wordCount;                                           // how many words are actually stored
} Category;
 
// GameState holds everything about the CURRENT round being played:
// the secret word, its hint, what the player has guessed so far,
// how many wrong guesses are left, the score, and whether the
// one-time hint has already been used.
typedef struct {
    char word[MAX_WORD_LENGTH];     // the secret word to guess
    char hint[MAX_WORD_LENGTH];     // the hint for that word
    char guessed[MAX_WORD_LENGTH];  // what the player sees, e.g. "_a__ha__" as letters are found
    int attemptsLeft;               // wrong guesses remaining before game over
    int score;                      // points earned this round
    int hintUsed;                   // 0 = hint not used yet, 1 = hint already used
} GameState;
 
// ===================== Function Prototypes =====================
// A prototype tells the compiler "this function exists and here is its
// signature" before it actually sees the full code for it. This lets
// functions call each other freely no matter what order they're written in
// below, and lets main() (at the bottom) call functions defined above it.
void loadCategories(Category categories[], int *categoryCount);
void printBanner(void);
void chooseWord(Category *category, GameState *game);
void displayHangman(int attemptsLeft);
void displayWord(GameState *game);
int guessLetter(GameState *game, char letter);
int isWordGuessed(GameState *game);
void showHint(GameState *game);
void updateScore(GameState *game, int won);
void toLowerCase(char *str);
void displayCategoryMenu(Category categories[], int categoryCount);
int getCategoryChoice(int categoryCount);
void playRound(GameState *game);
void showGameOverMessage(GameState *game, int won);
void saveScoreToFile(GameState *game);
void showScoreHistory(void);

//AYMAN-BIN-SALIM-----
// ===================== Function Definitions =====================
 
// ----- Word data (previously stored in data/words.txt, now built-in) -----
// This function fills the categories[] array with all the word/hint data.
// It used to read this from a text file; now the data is hardcoded directly
// in the code so the program doesn't need any external files to run.
void loadCategories(Category categories[], int *categoryCount) {
    int c = 0; // c = which category we're currently filling in (0, 1, 2...)
    int w = 0; // w = which word slot within that category we're filling in
 
    // ----- Technology -----
    strcpy(categories[c].name, "Technology"); // set this category's name
    w = 0; // reset word counter for this new category
    // Each line below stores one word, then its matching hint, then moves
    // to the next slot (w++). This repeats for every word in the category.
    strcpy(categories[c].words[w], "algorithm"); strcpy(categories[c].hints[w], "Step by step instructions to solve a problem"); w++;
    strcpy(categories[c].words[w], "keyboard"); strcpy(categories[c].hints[w], "Input device with keys you type on"); w++;
    strcpy(categories[c].words[w], "compiler"); strcpy(categories[c].hints[w], "Converts source code into machine code"); w++;
    strcpy(categories[c].words[w], "firewall"); strcpy(categories[c].hints[w], "Protects a network from unauthorized access"); w++;
    strcpy(categories[c].words[w], "bandwidth"); strcpy(categories[c].hints[w], "Amount of data that can be transferred over time"); w++;
    strcpy(categories[c].words[w], "debugging"); strcpy(categories[c].hints[w], "Process of finding and fixing errors in code"); w++;
    strcpy(categories[c].words[w], "processor"); strcpy(categories[c].hints[w], "The brain of a computer that executes instructions"); w++;
    strcpy(categories[c].words[w], "encryption"); strcpy(categories[c].hints[w], "Process of converting data into a secret code"); w++;
    categories[c].wordCount = w; // record how many words this category ended up with
    c++; // move on to the next category slot
 
    // ----- Hangman -----
    strcpy(categories[c].name, "Hangman");
    w = 0;
    strcpy(categories[c].words[w], "hangman"); strcpy(categories[c].hints[w], "a popular game to play with words"); w++;
    strcpy(categories[c].words[w], "scaffold"); strcpy(categories[c].hints[w], "Platform used for executions historically"); w++;
    strcpy(categories[c].words[w], "guess"); strcpy(categories[c].hints[w], "What you do when trying to find the letter"); w++;
    strcpy(categories[c].words[w], "alphabet"); strcpy(categories[c].hints[w], "Full set of 26 letters used in English"); w++;
    strcpy(categories[c].words[w], "letters"); strcpy(categories[c].hints[w], "Individual characters that make up a word"); w++;
    strcpy(categories[c].words[w], "puzzle"); strcpy(categories[c].hints[w], "A game or problem designed to test knowledge"); w++;
    strcpy(categories[c].words[w], "wordplay"); strcpy(categories[c].hints[w], "Clever or witty use of words"); w++;
    categories[c].wordCount = w;
    c++;
 
    // ----- CSE -----
    strcpy(categories[c].name, "CSE");
    w = 0;
    strcpy(categories[c].words[w], "recursion"); strcpy(categories[c].hints[w], "A function that calls itself"); w++;
    strcpy(categories[c].words[w], "pointer"); strcpy(categories[c].hints[w], "Variable that stores a memory address"); w++;
    strcpy(categories[c].words[w], "array"); strcpy(categories[c].hints[w], "Collection of elements stored in contiguous memory"); w++;
    strcpy(categories[c].words[w], "compiler"); strcpy(categories[c].hints[w], "Translates source code into machine code"); w++;
    strcpy(categories[c].words[w], "database"); strcpy(categories[c].hints[w], "Organized collection of structured data"); w++;
    strcpy(categories[c].words[w], "binary"); strcpy(categories[c].hints[w], "Number system using only 0s and 1s"); w++;
    strcpy(categories[c].words[w], "function"); strcpy(categories[c].hints[w], "Reusable block of code that performs a task"); w++;
    strcpy(categories[c].words[w], "variable"); strcpy(categories[c].hints[w], "Named storage location for data"); w++;
    strcpy(categories[c].words[w], "loop"); strcpy(categories[c].hints[w], "Structure that repeats a block of code"); w++;
    strcpy(categories[c].words[w], "stack"); strcpy(categories[c].hints[w], "Data structure that follows last in first out"); w++;
    categories[c].wordCount = w;
    c++;
 
    *categoryCount = c; // write the final total number of categories back to main()
                         // (a pointer is used here so this function can change
                         // main's categoryCount variable directly)


// ISRAT JAHAN JERIN-------
// =============== Print the HANGMAN ASCII art banner ====================
// Just decorative text shown once when the program starts.
void printBanner(void) {
    printf("\n");
    printf("  +-----------------------------------------------------------------+\n");
    printf("  |                                                                 |\n");
    printf("  |  ██╗  ██╗ █████╗ ███╗  ██╗ ██████╗ ███╗   ███╗ █████╗ ███╗  ██╗ |\n");
    printf("  |  ██║  ██║██╔══██╗████╗ ██║██╔════╝ ████╗ ████║██╔══██╗████╗ ██║ |\n");
    printf("  |  ███████║███████║██╔██╗██║██║  ███╗██╔████╔██║███████║██╔██╗██║ |\n");
    printf("  |  ██╔══██║██╔══██║██║╚████║██║   ██║██║╚██╔╝██║██╔══██║██║╚████║ |\n");
    printf("  |  ██║  ██║██║  ██║██║ ╚███║╚██████╔╝██║ ╚═╝ ██║██║  ██║██║ ╚███║ |\n");
    printf("  |  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚══╝ ╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚══╝ |\n");
    printf("  |                                                                 |\n");
    printf("  |            ██████╗  █████╗ ███╗   ███╗███████╗                  |\n");
    printf("  |           ██╔════╝ ██╔══██╗████╗ ████║██╔════╝                  |\n");
    printf("  |           ██║  ███╗███████║██╔████╔██║█████╗                    |\n");
    printf("  |           ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝                    |\n");
    printf("  |           ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗                  |\n");
    printf("  |            ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝                  |\n");
    printf("  |                                                                 |\n");
    printf("  |          Don't get hung before the HANGMAN!                     |\n");
    printf("  +----------------------------------------------------------------+\n\n");
}

// ----- Randomly choose a word from a category -----
// Picks one random word/hint pair from the chosen category and sets up
// a fresh GameState for a new round.
void chooseWord(Category *category, GameState *game) {
    srand(time(NULL));  // seed the random number generator using the current
                         // time, so we get a different random word each run
    int index = rand() % category->wordCount; // random index between 0 and wordCount-1

    strcpy(game->word, category->words[index]); // copy the chosen word into game state
    strcpy(game->hint, category->hints[index]);  // copy its matching hint
    game->attemptsLeft = MAX_ATTEMPTS; // reset wrong-guess counter to max
    game->score = 0;                   // reset score for this round

    // Build the "guessed" display string as a row of underscores,
    // one underscore per letter in the secret word.
    int len = strlen(game->word);
    for (int i = 0; i < len; i++) {
        game->guessed[i] = '_';
    }
    game->guessed[len] = '\0'; // null terminator marks the end of the string
}

// ----- Display hangman ASCII art based on attempts left -----
// A switch statement picks which picture to print depending on how many
// wrong guesses remain (6 = nothing drawn yet, 0 = fully hung figure).
void displayHangman(int attemptsLeft) {
    switch (attemptsLeft) {
        case 6:
            printf("  +---+\n      |\n      |\n      |\n     ===\n");
            break;
        case 5:
            printf("  +---+\n  O   |\n      |\n      |\n     ===\n");
            break;
        case 4:
            printf("  +---+\n  O   |\n  |   |\n      |\n     ===\n");
            break;
        case 3:
            printf("  +---+\n  O   |\n /|   |\n      |\n     ===\n");
            break;
        case 2:
            printf("  +---+\n  O   |\n /|\\  |\n      |\n     ===\n");
            break;
        case 1:
            printf("  +---+\n  O   |\n /|\\  |\n /    |\n     ===\n");
            break;
        case 0:
            printf("  +---+\n  O   |\n /|\\  |\n / \\  |\n     ===\n");
            break;
    }
}

// ----- Display the current guessed word -----
// Prints the word as the player currently sees it, e.g. "Word: _a__ha__"
void displayWord(GameState *game) {
    printf("Word: %s\n", game->guessed);
}

// ----- Process a single letter guess -----
// Checks the guessed letter against every letter in the secret word.
// If it matches anywhere, those positions get revealed in "guessed".
// If it doesn't match at all, one attempt is subtracted.
int guessLetter(GameState *game, char letter) {
    letter = tolower(letter); // make guesses case-insensitive
    int found = 0;            // tracks whether the letter was found anywhere
    int len = strlen(game->word);

    // Loop through every letter position in the secret word
    for (int i = 0; i < len; i++) {
        if (tolower(game->word[i]) == letter) {
            game->guessed[i] = game->word[i]; // reveal that letter
            found = 1;
        }
    }

    if (!found) {
        game->attemptsLeft--; // wrong guess costs one attempt
    }

    return found; // 1 if letter was correct, 0 if wrong
}

// ----- Check if the word has been fully guessed -----
// Compares the "guessed" string to the real word - if they're identical,
// every letter has been revealed and the player has won.
int isWordGuessed(GameState *game) {
    return strcmp(game->guessed, game->word) == 0;
}

// ----- Show hint (one-time use per game) -----
void showHint(GameState *game) {
    printf("Hint: %s\n", game->hint);
}

// ----- Update score based on win/loss -----
// Only awards points if the round was won; more attempts remaining
// means a higher score (10 points per attempt left).
void updateScore(GameState *game, int won) {
    if (won) {
        game->score += game->attemptsLeft * 10;
    }
}

// ----- Convert string to lowercase -----
// Utility function that walks through every character of a string
// and lowercases it in place. (Not currently called anywhere, but
// kept available as a helper.)
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) { // loop continues until it hits the '\0' end-of-string
        str[i] = tolower(str[i]);
    }
}


// TANZEEM HASAN--------
// ----- Show the numbered list of categories -----
// Loops through all loaded categories and prints them as a numbered menu.
void displayCategoryMenu(Category categories[], int categoryCount) {
    printf("Choose a category:\n");
    for (int i = 0; i < categoryCount; i++) {
        printf("%d. %s\n", i + 1, categories[i].name);
    }
}

// ----- Ask the player to pick a category and validate the input -----
// Reads a number from the keyboard and keeps asking until the player
// enters a valid category number.
int getCategoryChoice(int categoryCount) {
    int choice;
    int valid = 0; // becomes 1 once a valid choice is entered

    // Loop keeps asking until a valid number is typed
   //---------While-loop-------------(1)
    while (!valid) {
        printf("Enter choice (number): ");
        scanf("%d", &choice); // read an integer typed by the player

        if (choice < 1 || choice > categoryCount) {
            printf("Invalid choice. Please try again.\n");
        } else {
            valid = 1; // good input, stop looping
        }
    }

    return choice;
}

// ----- Handle a single guess: get input, apply it, show feedback -----
// This runs once per turn: show the current state, read one guess
// (a letter, or '?' for a hint), and apply it.
void playRound(GameState *game) {
    displayHangman(game->attemptsLeft); // show the current hangman picture
    displayWord(game);                  // show the word with blanks/found letters
    printf("Attempts left: %d\n", game->attemptsLeft);

    printf("Enter a letter to guess, or '?' for a hint: ");
    char input[10];
    scanf("%s", input); // read a short word/character from the keyboard

    char letter = input[0]; // only the first character typed is used

    if (letter == '?') {
        if (game->hintUsed == 0) {
            showHint(game);
            game->hintUsed = 1; // mark hint as used so it can't be used again
        } else {
            printf("You've already used your hint!\n");
        }
    } else {
        int found = guessLetter(game, letter);
        if (!found) {
            printf("Wrong guess!\n");
        }
    }

    printf("\n");
}

// ----- Print the win/loss message and update the score -----
// Called once after the game loop ends, to report the final outcome.
void showGameOverMessage(GameState *game, int won) {
    // Draw a line of dashes using a loop instead of a fixed string
   //---------for-loop-------------(2)
    for (int i = 0; i < 40; i++) {
        printf("-");
    }
    printf("\n");

    if (won) {
        printf("Congratulations! You guessed the word: %s\n", game->word);
        updateScore(game, 1);
    } else {
        displayHangman(0); // show the fully-hung figure on a loss
        printf("Game over! The word was: %s\n", game->word);
        updateScore(game, 0);
    }

    printf("Final score: %d\n", game->score);
}

