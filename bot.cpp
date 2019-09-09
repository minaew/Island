#include <random>
#include <chrono>
#include <iostream>

#include "bot.h"


Bot::Bot() : m_counter(0), m_direction(0), m_health(20)
{
    memory.resize(MEMORY_SIZE, 0);

    // some init program
    memory[2] = 4;
    memory[3] = 6;
    memory[4] = 1;
    memory[5] = 59;
    memory[6] = 2;
    memory[7] = 57;
}

Bot::Bot(std::vector<int> new_memory) : m_counter(0), m_direction(0), m_health(20)
{
    memory = new_memory;
}

void Bot::Resurect()
{
    m_counter = 0;
    m_direction = 0;
    m_health = 20;
}

bool Bot::IsDead() const
{
    return m_health == 0;
}

Bot::~Bot()
{
    field = nullptr;
}

void Bot::Reset()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, MEMORY_SIZE-1);

    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        memory[i] = distribution(generator);
    }
}

Bot Bot::Multiple()
{
    std::vector<int> new_memory(MEMORY_SIZE);
    std::copy(memory.begin(), memory.end(), new_memory.begin());

    const int number_of_mutated_cells = 5;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, MEMORY_SIZE-1);
    for (int i = 0; i < number_of_mutated_cells; i++)
    {
        int index = distribution(generator);
        int memory = distribution(generator);

        new_memory[index] = memory;
    }


    Bot b(new_memory);
    return b;
}

void Bot::Run()
{
/*
    std::cout << m_counter << ":"
              << memory[m_counter] << ":"
              << m_direction << std::endl;
*/


    switch (memory[m_counter])
    {
    case 0:
        Move();
        break;
    case 1:
        m_direction++;
        m_direction = m_direction % 4;
        m_counter++;
        m_counter = m_counter % MEMORY_SIZE;
        break;
    case 2:
        field->Consume(this, m_direction);
        m_health++;
        m_counter++;
        m_counter = m_counter % MEMORY_SIZE;
        break;

    default:
        m_counter += memory[m_counter];
        m_counter = m_counter % MEMORY_SIZE;
        break;
    }

    m_health--;
}

void Bot::Move()
{
    int grid_value = field->Watch(this, m_direction);

    switch (grid_value)
    {
        case GRID_EMPTY:
        //std::cout << "empty" << std::endl;
        field->Step(this, m_direction);
        m_counter += memory[m_counter+1];
        m_counter = m_counter % MEMORY_SIZE;
        break;

    case GRID_BLOCK:
        //std::cout << "block" << std::endl;
        m_counter += memory[m_counter+2];
        m_counter = m_counter % MEMORY_SIZE;
        break;

    case GRID_FOOD:
        //std::cout << "food" << std::endl;
        m_counter += memory[m_counter+3];
        m_counter = m_counter % MEMORY_SIZE;
        break;
    }
}
