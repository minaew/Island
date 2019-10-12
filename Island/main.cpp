#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>

#include "bot.h"
#include "fieldentry.h"
#include "field.h"

#define GENERATION_NUMBER (40)
#define FIELD_SIZE (30)

bool cmp(const std::tuple<Bot,int> &a, const std::tuple<Bot,int> &b)
{
    return std::get<1>(a) > std::get<1>(b);
}

void generation(std::vector<std::tuple<Bot, int>>& round, int number)
{
    for (unsigned i = 0; i < round.size(); i++)
    {
        std::string field_id = std::to_string(number) +  "_" + std::to_string(i);

        Field f(FIELD_SIZE, field_id); // genarate random square field
        Bot b = std::get<0>(round[i]);
        b.Resurect();
        f.Add(FIELD_SIZE/2, FIELD_SIZE/2, &b); // put bot in center

        // start simulation
        int life_time = 0;
        while (!b.IsDead())
        {
            b.Run();
            f.Render();
            life_time++;
        }

        // bot in dead
        std::tuple<Bot, int> t(b, life_time);
        round[i] = t;
    }

    // sort
    std::sort(round.begin(), round.end(), cmp);

    // print top lifetime
    for (int i = 0; i < 5; i++)
    {
        std::cout << std::get<1>(round[i]) << std::endl;
    }

    // print top program
    std::get<0>(round.at(0)).RenderProgram();
    std::cout << "===================================" << std::endl;


    // create new 100 from top 10
    for (int i = 0; i < 9; i++)
    {
        Bot bot = std::get<0>(round[i]);
        for (int j = 0; j < 10; j++)
        {
            Bot child = bot.Multiple();
            std::tuple<Bot, int> t(child, 0);
            round[(i+1)*10 + j] = t;
        }
    }
}

int main()
{
    // create and 100 bots
    std::vector<std::tuple<Bot, int>> round(100);
    for (unsigned i = 0; i < round.size(); i++)
    {
        Bot b;
        std::tuple<Bot, int> t(b, 0);
        round.at(i) = t;
    }

    for (int i = 0; i < GENERATION_NUMBER; i++)
    {
        generation(round, i);
    }
}
