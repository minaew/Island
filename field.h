#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <string>
#include <fstream>

#include "fieldentry.h"
#include "bot.h"
class Bot; // FIXME: shit design

// TODO: enum
#define GRID_EMPTY (0)
#define GRID_BLOCK (1)
#define GRID_FOOD (2)

class Field
{
    public:
        Field(int size, std::string id);
        virtual ~Field();
        void Add(int x, int y, Bot* bot);
        void Render();
        int Watch(Bot* bot, int direction);
        void Step(Bot* bot, int direction);
        void Consume(Bot* bot, int direction);

    private:
        int m_size;
        std::vector<int> grid;
        std::vector<FieldEntry> bots;
        std::ofstream os;
};

#endif // FIELD_H
