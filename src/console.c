#include <Windows.h>
#include <stdio.h>

#include "console.h"
#include "Color.h"
#include "MessageColor.h"

#define DEFAULT_CONSOLE_TEXT_COLOR white

void setConsoleTextColor(Color color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetConsoleTextColorToDefault() {
    setConsoleTextColor(DEFAULT_CONSOLE_TEXT_COLOR);
}

void pauseUntilUserResponds() {
    setConsoleTextColor(COLOR_INPUT);
    printf("  ");
    system("pause");
    resetConsoleTextColorToDefault();
}

void clearConsole() {
    system("cls");
}