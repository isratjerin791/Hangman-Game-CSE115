#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
