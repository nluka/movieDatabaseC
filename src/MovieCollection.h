#ifndef MOVIE_ARRAY_H
#define MOVIE_ARRAY_H

#include "Movie.h"
#include "constants.h"

typedef struct {
  Movie entries[MAX_MOVIE_COUNT];
  int length;
} MovieCollection;

void sortMovieCollectionEntries(MovieCollection *movieCollection);

void removeMovieFromMovieCollectionEntries(MovieCollection *movieCollectionPtr, int movieIndex);

#endif