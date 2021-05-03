#ifndef APP_LOOP_H
#define APP_LOOP_H

#include <stdio.h>
#include <stdbool.h>

#include "Action.h"
#include "Movie.h"
#include "MovieCollection.h"

void appLoop();

void doAction(Action action);

void addMovie();

const char* getUniqueMovieId();

const char* getValidOrBlankMovieId();

const char* getValidOrBlankMovieTitle(char* emptytFieldInfoString);

int getValidOrZeroMovieQuantity(char* zeroFieldValueInfoString);

double getValidOrZeroMoviePrice(char* zeroFieldValueInfoString);

void updateMovie();

Movie* getMoviePtrById(const char* id);

const char* getExistingOrBlankMovieId(char* emptyFieldInfoString);

bool updateMovieTitle(Movie *moviePtr);

bool updateMovieQuantity(Movie *moviePtr);

bool updateMoviePrice(Movie *moviePtr);

int getMovieIndexInCollectionById(const char *searchId);

void deleteMovie();

void listMovies();

#endif