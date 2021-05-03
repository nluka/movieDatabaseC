#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <string.h>
#include <windows.h>

#include "appLoop.h"
#include "menu.h"
#include "Action.h"
#include "input.h"
#include "util.h"
#include "globals.h"
#include "MessageColor.h"
#include "console.h"
#include "MovieCollection.h"
#include "ExitCode.h"

void appLoop() {
    while (true) {
        printMainMenu();
        Action action = getActionChoiceFromUser();
        if (action == EXIT) {
            return;
        }
        doAction(action);
    }
}

void doAction(Action action) {
    switch (action) {
    case ADD_MOVIE:
        addMovie();
        break;
    case UPDATE_MOVIE:
        updateMovie();
        break;
    case DELETE_MOVIE:
        deleteMovie();
        break;
    case LIST_MOVIES:
        listMovies();
        break;
    default:
        printStringColored("  ERROR: invalid selection\n", COLOR_ERROR);
        Sleep(2000);
        break;
    }
}

void addMovie() {
    clearConsole();
    printAddMovieMenuHeader();
    printMovieTable();

    const char* id = getUniqueMovieId("  Note: leave entry blank to abort\n");
    if (getStringLengthNulTerminated(id) == 0) {
        free((char*)id);
        return;
    }

    const char* title = getValidOrBlankMovieTitle("  Note: leave entry blank to abort\n");
    if (getStringLengthNulTerminated(title) == 0) {
        free((char*)title);
        return;
    }

    int quantity = getValidOrZeroMovieQuantity("  Note: leave entry blank to abort\n");
    if (quantity == 0) {
        return;
    }

    double price = getValidOrZeroMoviePrice("  Note: leave entry blank to abort\n");
    if (price == 0) {
        return;
    }

    Movie newMovie;
    strcpy(newMovie.id, id);
    strcpy(newMovie.title, title);
    newMovie.quantity = quantity;
    newMovie.price = price;

    free((char*)id);
    free((char*)title);

    movieCollection.entries[movieCollection.length] = newMovie;
    movieCollection.length++;
}

const char* getUniqueMovieId() {
    const char* id;

    while (true) {
        printInputPromptForMovieId("  Note: leave entry blank to abort\n");
        id = getValidOrBlankMovieId();
        
        int movieIndex = getMovieIndexInCollectionById(id);
        if (movieIndex == -1) {
            break;
        }
        printStringColored("  ERROR: inputted UPC/SKU number already exists\n", COLOR_ERROR);
    }

    return id;
}

const char* getValidOrBlankMovieId() {
    int idCharCount = (MAX_MOVIE_ID_LENGTH + 1);
    char *idTemp = malloc(sizeof(char) * idCharCount);
    exitIfPointerIsNull(idTemp);

    fgets(idTemp, MAX_MOVIE_ID_LENGTH, stdin);
    strcpy(idTemp, getStringWithNewlineCharReplacedByNulChar(idTemp, idCharCount));

    const char* idActual = (const char*) malloc(sizeof(char) * idCharCount);
    exitIfPointerIsNull(idActual);

    strcpy((char*)idActual, idTemp);
    return idActual;
}

const char* getValidOrBlankMovieTitle(char *emptytFieldInfoString) {
    int titleCharCount = MAX_MOVIE_TITLE_LENGTH + 1;
    char *titleTemp = malloc(sizeof(char) * titleCharCount);
    exitIfPointerIsNull(titleTemp);

    printInputPromptForMovieTitle(emptytFieldInfoString);
    fgets(titleTemp, titleCharCount, stdin);
    strcpy(titleTemp, getStringWithNewlineCharReplacedByNulChar(titleTemp, titleCharCount));

    const char* titleActual = (const char*) malloc(sizeof(char) * titleCharCount);
    exitIfPointerIsNull(titleActual);

    strcpy((char*)titleActual, titleTemp);
    return titleActual;
}

int getValidOrZeroMovieQuantity(char *zeroFieldValueInfoString) {
    int quantity;
    while (true) {
        printInputPromptForMovieQuantity(zeroFieldValueInfoString);
        quantity = getIntFromUser();
        if (quantity >= 0) {
            return quantity;
        }
        printStringColored("  ERROR: invalid quantity\n", COLOR_ERROR);
    }
}

double getValidOrZeroMoviePrice(char* zeroFieldValueInfoString) {
    double price;
    while (true) {
        printInputPromptForMoviePrice(zeroFieldValueInfoString);
        price = getDoubleFromUser();
        if (price >= 0) {
            return price;
        }
        printStringColored("  ERROR: invalid price\n", COLOR_ERROR);
    }
}

void updateMovie() {
    clearConsole();
    printUpdateMovieMenuHeader();
    printMovieTable();

    const char* id = getExistingOrBlankMovieId("  Note: leave entry blank to abort\n");
    if (getStringLengthNulTerminated(id) == 0) {
        free((char*)id);
        return;
    }
    
    Movie* moviePtr = getMoviePtrById(id);
    free((char*)id);
    exitIfPointerIsNull(moviePtr);

    updateMovieTitle(moviePtr);
    updateMovieQuantity(moviePtr);
    updateMoviePrice(moviePtr);
}

Movie* getMoviePtrById(const char *id) {
    int movieIndex = getMovieIndexInCollectionById(id);
    if (movieIndex == -1) {
        return NULL;
    }
    return &(movieCollection.entries[movieIndex]);
}

const char* getExistingOrBlankMovieId(char *emptyFieldInfoString) {
    const char* id;
    int movieIndex;

    while (true) {
        printInputPromptForMovieId(emptyFieldInfoString);
        id = getValidOrBlankMovieId();
        if (getStringLengthNulTerminated(id) == 0) {
            return id;
        }
        movieIndex = getMovieIndexInCollectionById(id);
        if (movieIndex > -1) {
            return id;
        }
        printStringColored("  ERROR: movie not found\n", COLOR_ERROR);
    }
}

bool updateMovieTitle(Movie* moviePtr) {
    const char* newTitle = getValidOrBlankMovieTitle("  Note: leave entry blank to keep current value\n");
    if (getStringLengthNulTerminated(newTitle) == 0) {
        free((char*)newTitle);
        return false;
    }
    strcpy(moviePtr->title, newTitle);
    free((char*)newTitle);
    return true;
}

bool updateMovieQuantity(Movie* moviePtr) {
    int newQuantity = getValidOrZeroMovieQuantity("  Note: enter zero to keep current value\n");
    if (newQuantity == 0) {
        return false;
    }
    moviePtr->quantity = newQuantity;
    return true;
}

bool updateMoviePrice(Movie* moviePtr) {
    double newPrice = getValidOrZeroMoviePrice("  Note: enter zero to keep current value\n");
    if (newPrice == 0) {
        return false;
    }
    moviePtr->price = newPrice;
    return true;
}

int getMovieIndexInCollectionById(const char *searchId) {
    for (int i = 0; i < movieCollection.length; i++) {
        if (strcmp(movieCollection.entries[i].id, searchId) == 0) {
            return i;
        }
    }
    return -1;
}

void deleteMovie() {
    clearConsole();
    printDeleteMovieMenuHeader();
    printMovieTable();

    const char* id = getExistingOrBlankMovieId("  Note: leave entry blank to abort\n");
    if (getStringLengthNulTerminated(id) == 0) {
        free((char*)id);
        return;
    }

    Movie* moviePtr = getMoviePtrById(id);
    int movieIndex = getMovieIndexInCollectionById(id);
    free((char*)id);
    exitIfPointerIsNull(moviePtr);

    printMovieDeletionVerificationPrompt(moviePtr);
    bool shouldMovieBeDeleted = getBoolFromUser();

    if (!shouldMovieBeDeleted) {
        return;
    }

    removeMovieFromMovieCollectionEntries(&movieCollection, movieIndex);
    printMovieDeletionSuccessPrompt();
    pauseUntilUserResponds();
}

void listMovies() {
    clearConsole();
    printListMoviesMenuHeader();
    printMovieTable();
    printBlankLine();
    pauseUntilUserResponds();
}