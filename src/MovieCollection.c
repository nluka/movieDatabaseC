#define _CRT_SECURE_NO_WARNINGS

#include <string.h>

#include "MovieCollection.h"

void sortMovieCollectionEntries(MovieCollection* movieCollectionPtr) {
    Movie temp;
    for (int i = 0; i < movieCollectionPtr->length - 1; i++) {
        for (int j = i + 1; j < movieCollectionPtr->length; j++) {
            char title1[MAX_MOVIE_TITLE_LENGTH + 1];
            char title2[MAX_MOVIE_TITLE_LENGTH + 1];

            strcpy(title1, (movieCollectionPtr->entries + i)->title);
            strcpy(title2, (movieCollectionPtr->entries + j)->title);

            if (strcmp(title1, title2) <= 0) {
                continue;
            }

            temp = *(movieCollectionPtr->entries + i);
            *(movieCollectionPtr->entries + i) = *(movieCollectionPtr->entries + j);
            *(movieCollectionPtr->entries + j) = temp;
        }
    }
}

void removeMovieFromMovieCollectionEntries(MovieCollection* movieCollectionPtr, int movieIndex) {
    int movieCount = movieCollectionPtr->length;
    Movie temp = *(movieCollectionPtr->entries + (movieCount - 1));
    *(movieCollectionPtr->entries + (movieCount - 1)) = *(movieCollectionPtr->entries + movieIndex);
    *(movieCollectionPtr->entries + movieIndex) = temp;
    movieCollectionPtr->length = movieCount - 1;
}