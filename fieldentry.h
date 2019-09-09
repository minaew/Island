#ifndef FIELDENTRY_H
#define FIELDENTRY_H

#include "bot.h"
class Bot;

struct FieldEntry
{
    int x;
    int y;
    Bot* bot;
};

#endif // FIELDENTRY_H
