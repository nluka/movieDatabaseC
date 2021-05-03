#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "input.h"
#include "Action.h"
#include "Movie.h"

void clearInputBuffer() {
    while ((getchar()) != '\n');
}

Action getActionChoiceFromUser() {
    char actionChar = getchar();

    //scanf_s("%c", &actionChar, 1);
    clearInputBuffer();

    return convertCharToAction(actionChar);
}

Action convertCharToAction(char actionChar) {
    Action action = NO_ACTION;
    switch (tolower(actionChar)) {
    case 'a':
        action = ADD_MOVIE;
        break;
    case 'u':
        action = UPDATE_MOVIE;
        break;
    case 'd':
        action = DELETE_MOVIE;
        break;
    case 'l':
        action = LIST_MOVIES;
        break;
    case 'e':
        action = EXIT;
        break;
    default:
        break;
    }
    return action;
}

int getIntFromUser() {
    char input[MAX_MOVIE_QUANTITY_DIGITS];
    fgets(input, MAX_MOVIE_QUANTITY_DIGITS, stdin);
    return atoi(input);
}

double getDoubleFromUser() {
    char input[MAX_MOVIE_PRICE_DIGITS];
    fgets(input, MAX_MOVIE_PRICE_DIGITS, stdin);
    return strtod(input, NULL);
}

bool getBoolFromUser() {
    char choice = getchar();
    clearInputBuffer();
    if (tolower(choice) == 'n') {
        return false;
    }
    return true;
}