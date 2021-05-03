#define _CRT_SECURE_NO_WARNINGS

#include "initialize.h"
#include "console.h"
#include "menu.h"
#include "globals.h"
#include "MessageColor.h"

void initialize() {
    resetConsoleTextColorToDefault();

    movieCollectionDataFilePtr = fopen(DATA_FILE_NAME, "rb");

    printBlankLine();
    if (movieCollectionDataFilePtr == NULL) {
        printStringColored("  movieCollection.txt not found, will create new file upon exit.\n", COLOR_WARNING);
        movieCollection.length = 0;
        pauseUntilUserResponds();
        return;
    }
    printStringColored("  movieCollection.txt found.\n", COLOR_SUCCESS);
    loadMovieCollection();
    fclose(movieCollectionDataFilePtr);
    pauseUntilUserResponds();
    clearConsole();
}

void loadMovieCollection() {
    loadMovieCount(movieCollection, movieCollectionDataFilePtr);
    loadMovies(movieCollection, movieCollectionDataFilePtr);
}

void loadMovieCount() {
    printString("  Retrieving movie count... ");
    readMovieCountFromDataFile(movieCollection, movieCollectionDataFilePtr);
    printStringColored("done ", COLOR_SUCCESS);
    printString("(");
    printIntColored(movieCollection.length, blue);
    printString(")\n");
}

void readMovieCountFromDataFile() {
    fread(&movieCollection.length, sizeof(movieCollection.length), 1, movieCollectionDataFilePtr);
}

void loadMovies() {
    for (int i = 0; i < movieCollection.length; i++) {
        printString("  Loading movie ");
        printInt(i + 1);
        printString("... ");
        readMovieFromDataFile(i);
        printStringColored("done\n", COLOR_SUCCESS);
    }
}

void readMovieFromDataFile(int movieNumber) {
    fread(&movieCollection.entries[movieNumber], sizeof(Movie), 1, movieCollectionDataFilePtr);
}