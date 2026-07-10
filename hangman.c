#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "hangman.h"

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
