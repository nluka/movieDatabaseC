#ifndef WRITE_DATA_FILES_H
#define WRITE_DATA_FILES_H

#include <stdio.h>

#include "MovieCollection.h"

void writeDataFiles();

void saveMovies(FILE *filePtr, MovieCollection *movieCollectionPtr);

#endif