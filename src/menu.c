#include "menu.h"
#include "console.h"
#include "MessageColor.h"
#include "Movie.h"
#include "globals.h"

void printString(char text[]) {
    printf("%s", text);
}

void printInt(int integer) {
    printf("%i", integer);
}

void printStringColored(char text[], Color color) {
    setConsoleTextColor(color);
    printString(text);
    resetConsoleTextColorToDefault();
}

void printIntColored(int integer, Color color) {
    setConsoleTextColor(color);
    printInt(integer);
    resetConsoleTextColorToDefault();
}

void printBlankLine() {
    printf("\n");
}

#pragma region Menus/Headers

void printMainMenu() {
    clearConsole();
    printBlankLine();
    printStringColored("  MAIN MENU\n", COLOR_HEADER);
    printStringColored("  #########\n", COLOR_HEADER);
    printBlankLine();
    printString("  (A)dd new movie\n");
    printString("  (U)pdate a movie\n");
    printString("  (D)elete a movie\n");
    printString("  (L)ist all entries\n");
    printString("  (E)xit\n");
    printBlankLine();
    printInputPromptForAction();
}

void printAddMovieMenuHeader() {
    printBlankLine();
    printStringColored("  ADD MOVIE MENU\n", COLOR_HEADER);
    printStringColored("  ##############\n", COLOR_HEADER);
    printBlankLine();
}

void printUpdateMovieMenuHeader() {
    printBlankLine();
    printStringColored("  UPDATE MOVIE MENU\n", COLOR_HEADER);
    printStringColored("  #################\n", COLOR_HEADER);
    printBlankLine();
}

void printDeleteMovieMenuHeader() {
    printBlankLine();
    printStringColored("  DELETE MOVIE MENU\n", COLOR_HEADER);
    printStringColored("  #################\n", COLOR_HEADER);
    printBlankLine();
}

void printListMoviesMenuHeader() {
    printBlankLine();
    printStringColored("  MOVIES LIST MENU\n", COLOR_HEADER);
    printStringColored("  #################\n", COLOR_HEADER);
    printBlankLine();
}

#pragma endregion

#pragma region Prompts

void printInputPromptForAction() {
    printStringColored("  > Enter a menu selection: ", COLOR_INPUT);
}

void printInputPromptForMovieId(char* emptytFieldInfoString) {
    printBlankLine();
    printStringColored(emptytFieldInfoString, COLOR_INFO);
    printStringColored("  > Enter the movie UPC/SKU number (1-12 characters): ", COLOR_INPUT);
}

void printInputPromptForMovieTitle(char* emptytFieldInfoString) {
    printBlankLine();
    printStringColored(emptytFieldInfoString, COLOR_INFO);
    printStringColored("  > Enter the movie title (1-30 characters): ", COLOR_INPUT);
}

void printInputPromptForMovieQuantity(char *zeroFieldValueInfoString) {
    printBlankLine();
    printStringColored(zeroFieldValueInfoString, COLOR_INFO);
    printStringColored("  > Enter the movie quantity (up to 8 digits): ", COLOR_INPUT);
}

void printInputPromptForMoviePrice(char* zeroFieldValueInfoString) {
    printBlankLine();
    printStringColored(zeroFieldValueInfoString, COLOR_INFO);
    printStringColored("  > Enter the movie price (> 0): ", COLOR_INPUT);
    printString("$");
}

void printExitPromptForListMoviesMenu() {
    printStringColored("  Press any key to return to main menu ", COLOR_INPUT);
}

void printMovieDeletionVerificationPrompt(Movie* moviePtr) {
    printBlankLine();
    printMovieTableHeader();
    printMovieTableRowSeparator();
    printMovieEntry(moviePtr);
    printStringColored("\n  Are you sure you want to delete this move? (y/n): ", COLOR_INPUT);
}

void printMovieDeletionSuccessPrompt() {
    printStringColored("\n  Movie successfully deleted.\n", COLOR_SUCCESS);
}

#pragma endregion

#pragma region Movie Table

void printMovieTable() {
    if (movieCollection.length < 1) {
        printString("  No entries currently in storage.\n");
        return;
    }

    sortMovieCollectionEntries(&movieCollection);

    printMovieTableHeader();
    for (int i = 0; i < movieCollection.length; i++) {
        printMovieTableRowSeparator();
        printMovieEntry(&movieCollection.entries[i]);
    }
}

void printMovieTableHeader() {
    printStringColored("  Movie Title                    ", blue);
    printMovieTableColumnSeparator();
    printStringColored(" UPC/SKU Number ", blue);
    printMovieTableColumnSeparator();
    printStringColored(" Quantity ", blue);
    printMovieTableColumnSeparator();
    printStringColored(" Price ($)\n", blue);
}

void printMovieTableColumnSeparator() {
    printStringColored("|", blue);
}

void printMovieTableRowSeparator() {
    printStringColored("  -------------------------------+----------------+----------+-----------\n", blue);
}

void printMovieEntry(Movie* moviePtr) {
    printf("  %-30s ", moviePtr->title);
    printMovieTableColumnSeparator();
    printf(" %-14s ", moviePtr->id);
    printMovieTableColumnSeparator();
    printf(" %-8d ", moviePtr->quantity);
    printMovieTableColumnSeparator();
    printf(" %.2lf\n", moviePtr->price);
}

#pragma endregion