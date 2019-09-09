#ifndef BOT_H
#define BOT_H

#include <vector>

#define MEMORY_SIZE (64)

#include "field.h"
class Field; // FIXME: shit design

class Bot
{
    public:
        Bot();
        virtual ~Bot();
        void Run();
        bool IsDead() const;
        void Reset();
        Bot Multiple();
        void Resurect();

        Field* field;

    protected:

    private:
        Bot(std::vector<int> memory);
        void Move();

        int m_counter;
        int m_direction;
        int m_health;

        std::vector<int> memory;
};

#endif // BOT_H
