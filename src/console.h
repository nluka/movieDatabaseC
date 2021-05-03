#ifndef CONSOLE_H
#define CONSOLE_H

#include "Color.h"

void setConsoleTextColor(Color color);

void resetConsoleTextColorToDefault();

void pauseUntilUserResponds();

void clearConsole();

#endif