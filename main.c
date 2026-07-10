#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hangman.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main(void) {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    printBanner();

    
  return 0;
}