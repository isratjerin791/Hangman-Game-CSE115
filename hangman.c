#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "hangman.h"

// ----- Load categories from words.txt -----
void loadCategories(Category categories[], int *categoryCount) {
    FILE *file = fopen("data/words.txt", "r");

    if (file == NULL) {
        printf("Error: Could not open data/words.txt\n");
        exit(1);
    }

    char line[100];
    int catIndex = -1;

    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            continue; // skip blank lines
        }

        if (line[0] == '#') {
            // New category
            catIndex++;
            strcpy(categories[catIndex].name, line + 1); // skip the '#'
            categories[catIndex].wordCount = 0;
        } else {
            // word,hint line
            char *word = strtok(line, ",");
            char *hint = strtok(NULL, ",");

            if (word != NULL && hint != NULL && catIndex >= 0) {
                int idx = categories[catIndex].wordCount;
                strcpy(categories[catIndex].words[idx], word);
                strcpy(categories[catIndex].hints[idx], hint);
                categories[catIndex].wordCount++;
            }
        }
    }

    *categoryCount = catIndex + 1;
    fclose(file);
}


// ----- Print the HANGMAN ASCII art banner -----
void printBanner(void) {
 printf("\n");
  printf("  +-------------------------------------------------------------------+\n");
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
    printf("  +-----------------------------------------------------------------+\n\n");
}

// ----- Randomly choose a word from a category -----
void chooseWord(Category *category, GameState *game) {
    srand(time(NULL));
    int index = rand() % category->wordCount;

    strcpy(game->word, category->words[index]);
    strcpy(game->hint, category->hints[index]);
    game->attemptsLeft = MAX_ATTEMPTS;
    game->score = 0;

    int len = strlen(game->word);
    for (int i = 0; i < len; i++) {
        game->guessed[i] = '_';
    }
    game->guessed[len] = '\0';
}

// ----- Display hangman ASCII art based on attempts left -----
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
