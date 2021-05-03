#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "writeDataFiles.h"
#include "MovieCollection.h"
#include "MessageColor.h"
#include "console.h"
#include "menu.h"
#include "globals.h"

void writeDataFiles() {
    saveMovies(movieCollectionDataFilePtr, &movieCollection);
}

void saveMovies(FILE* filePtr, MovieCollection* movieCollectionPtr) {
    clearConsole();

    printBlankLine();
    printString("  Opening file... ");
    filePtr = fopen(DATA_FILE_NAME, "wb");
    if (filePtr == NULL) {
        printStringColored("failed\n", COLOR_ERROR);
        exit(1);
    }
    printStringColored("done\n", COLOR_SUCCESS);

    printString("  Writing movie count... ");
    int movieCount = movieCollectionPtr->length;
    fwrite(&movieCount, sizeof(movieCount), 1, filePtr);
    printStringColored("done ", COLOR_SUCCESS);
    printString("(found ");
    printIntColored(movieCount, blue);
    printString(" movies)\n");

    for (int i = 0; i < movieCount; i++) {
        printString("  Writing data for movie ");
        printIntColored(i + 1, blue);
        printString("... ");
        fwrite(&movieCollectionPtr->entries[i], sizeof(Movie), 1, filePtr);
        printStringColored("done\n", COLOR_SUCCESS);
    }

    printString("  Closing file... ");
    fclose(filePtr);
    printStringColored("done\n", COLOR_SUCCESS);
    pauseUntilUserResponds();
}