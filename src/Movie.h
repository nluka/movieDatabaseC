#ifndef MOVIE_H
#define MOVIE_H

#include "constants.h"

// typedef char* Title;
// typedef char* Id;
// typedef int Quantity;
// typedef double Price;

typedef struct movie {
	char id[MAX_MOVIE_ID_LENGTH + 1];
	char title[MAX_MOVIE_TITLE_LENGTH + 1];
	int quantity;
	double price;
} Movie;

#endif