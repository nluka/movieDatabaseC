#include <stdio.h>
#include <windows.h>

#include "initialize.h"
#include "appLoop.h"
#include "writeDataFiles.h"
#include "globals.h"
#include "MovieCollection.h"

int main(int argc, char* argv[]) {
    initialize();
    appLoop();
    writeDataFiles();

    return 0;
}