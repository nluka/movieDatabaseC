#ifndef MESSAGE_COLOR_H
#define MESSAGE_COLOR_H

#include "Color.h"

typedef enum {
  COLOR_SUCCESS = green,
  COLOR_INPUT = lightblue,
  COLOR_ERROR = red,
  COLOR_WARNING = orange,
  COLOR_HEADER = purple,
  COLOR_INFO = grey
} MessageColor;

#endif