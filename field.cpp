#include "field.h"

#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

Field::Field(int size)
{
    m_size = size;
    grid.resize(m_size*m_size);
    for (int i = 0; i < size*size; i++)
    {
        grid[i] = GRID_EMPTY;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, size*size);

    for (int i = 0; i < size*size/20; i++)
    {
        grid[distribution(generator)] = GRID_BLOCK;
    }

    for (int i = 0; i < size*size/40; i++)
    {
        grid[distribution(generator)] = GRID_FOOD;
    }
}


Field::~Field()
{
}


void Field::Add(int x, int y, Bot* bot)
{
    bot->field = this;
    FieldEntry entry { x, y, bot };
    bots.push_back(entry);
}

int Field::Watch(Bot* bot, int direction)
{
    auto it = std::find_if(bots.begin(), bots.end(), [bot](FieldEntry entry)
                                   {
                                       return entry.bot == bot;
                                   });
    if (it == bots.end())
    {
        return GRID_BLOCK;
    }

    int nextx;
    int nexty;
    switch (direction)
    {
    case 0:
        nextx = it->x;
        nexty = it->y - 1;
        break;

    case 1:
        nextx = it->x + 1;
        nexty = it->y;
        break;

    case 2:
        nextx = it->x;
        nexty = it->y + 1;
        break;

    case 3:
        nextx = it->x - 1;
        nexty = it->y;
        break;
    }

    if (nextx < 0 || nextx > m_size-1 ||
        nexty < 0 || nexty > m_size-1)
    {
        return GRID_BLOCK;
    }

    return grid[nextx + nexty*m_size];
}

void Field::Step(Bot* bot, int direction)
{
    auto it = std::find_if(bots.begin(), bots.end(), [bot](FieldEntry entry)
                                   {
                                       return entry.bot == bot;
                                   });
    if (it == bots.end())
    {
        return;
    }
    switch (direction)
    {
    case 0:
        it->y--;
        break;

    case 1:
        it->x++;
        break;

    case 2:
        it->y++;
        break;

    case 3:
        it->x--;
        break;
    }
}

void Field::Consume(Bot* bot, int direction)
{
    auto it = std::find_if(bots.begin(), bots.end(), [bot](FieldEntry entry)
                                   {
                                       return entry.bot == bot;
                                   });
    if (it == bots.end())
    {
        return;
    }

    int new_x = it->x;
    int new_y = it->y;
    switch (direction)
    {
    case 0:
        new_y--;
        break;

    case 1:
        new_x++;
        break;

    case 2:
        new_y++;
        break;

    case 3:
        new_x--;
        break;
    }

    grid[new_x + new_y*m_size] = GRID_EMPTY;
}

void Field::Render()
{
    std::ostream* os;
    os = new std::ofstream("out.txt");

    for (int y = 0; y < m_size; y++)
    {
        for (int x = 0; x < m_size; x++)
        {
            // find bot
            auto it = std::find_if(bots.begin(), bots.end(), [x,y](FieldEntry entry)
                                   {
                                       return (entry.x == x) && (entry.y == y);
                                   });
            if (it == bots.end())
            {
                switch (grid[x + y*m_size])
                {
                    case GRID_EMPTY:
                        *os << "-\t";
                        break;

                    case GRID_BLOCK:
                        *os << "B\t";
                        break;

                    case GRID_FOOD:
                        *os << "F\t";
                        break;
                }

            }
            else
            {
                *os << "X\t";
            }
        }
        *os << std::endl;
    }

    *os << "---------------------------------------------------------------------------" << std::endl;

    delete os;
}
