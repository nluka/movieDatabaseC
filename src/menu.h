#ifndef MENU_H
#define MENU_H

#include "Color.h"
#include "Movie.h"

void printString(char text[]);

void printInt(int integer);

void printStringColored(char text[], Color color);

void printIntColored(int integer, Color color);

void printBlankLine();

#pragma region Menus/Headers

void printMainMenu();

void printAddMovieMenuHeader();

void printUpdateMovieMenuHeader();

void printDeleteMovieMenuHeader();

void printListMoviesMenuHeader();

#pragma endregion

#pragma region Prompts

void printInputPromptForAction();

void printInputPromptForMovieId(char* emptytFieldInfoString);

void printInputPromptForMovieTitle(char* emptytFieldInfoString);

void printInputPromptForMovieQuantity(char *zeroFieldValueInfoString);

void printInputPromptForMoviePrice(char* zeroFieldValueInfoString);

void printExitPromptForListMoviesMenu();

void printMovieDeletionVerificationPrompt(Movie *moviePtr);

void printMovieDeletionSuccessPrompt();

#pragma endregion

#pragma region Movie Table

void printMovieTable();

void printMovieTableHeader();

void printMovieTableColumnSeparator();

void printMovieTableRowSeparator();

void printMovieEntry(Movie *moviePtr);

#pragma endregion

#endif