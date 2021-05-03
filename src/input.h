#ifndef INPUT_H
#define INPUT_H

#include "Action.h"
#include "Movie.h"

void clearInputBuffer();

Action getActionChoiceFromUser();

Action convertCharToAction(char actionChar);

int getIntFromUser();

double getDoubleFromUser();

bool getBoolFromUser();

#endif