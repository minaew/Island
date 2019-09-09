#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#include "bot.h"
#include "fieldentry.h"
#include "field.h"


bool cmp(const std::tuple<Bot,int> &a, const std::tuple<Bot,int> &b)
{
    return std::get<1>(a) >= std::get<1>(b);
}

int main()
{
    // create and run 100 bots
    std::vector<std::tuple<Bot, int>> round;
    for (int i = 0; i < 100; i++)
    {
        Field f(10);
        Bot b;
        b.Reset();
        f.Add(5, 5, &b);

        int life_time = 0;
        while (!b.IsDead())
        {
            b.Run();
            life_time++;
        }

        std::tuple<Bot, int> t(b, life_time);
        round.push_back(t);
    }

    // take top 10
    std::sort(round.begin(), round.end(), cmp);

    for (int i = 0; i < 100; i++)
    {
        std::cout << std::get<1>(round[i]) << std::endl;
    }
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


    // run next 10 + new 90
    for (int i = 0; i < 100; i++)
    {
        Field f(10);
        Bot b = std::get<0>(round[i]);
        b.Resurect();
        f.Add(5, 5, &b);

        int life_time = 0;
        while (!b.IsDead())
        {
            b.Run();
            life_time++;
        }

        std::tuple<Bot, int> t(b, life_time);
        round[i] = t;
    }

    // take top 10
    std::sort(round.begin(), round.end(), cmp);
    for (int i = 0; i < 100; i++)
    {
        std::cout << std::get<1>(round[i]) << std::endl;
    }

    return 0;
}
