//https://leetcode.com/problems/trapping-rain-water/
#include <cstdlib>
#include <iostream>
#include <memory>
#include "cryless/cry.h"
#include <vector>
#include <thread>
#include <string>
#include <future>

int calc_rain(const std::vector<int> &input)
{
    std::vector<int> levels;
    int end = 0;
    bool temp_state = false;
    for(auto index : input)
    {
        for(int i = levels.size(); i < index * (levels.size() <= index); i++)
            levels.push_back(0);
        for(auto [i, lvl] : cry::enumerate(levels))
        {
            temp_state = (i + 1 > index);
            end += lvl * !temp_state;
            lvl = lvl * temp_state + temp_state;
        }
    }
    return end;
}

int one_row(std::vector<int>::const_iterator index, std::vector<int>::const_iterator stop, const int level)
{
    int val = 0;
    int end = 0;
    std::future<int> uf;
    bool father = false;

    auto calc = [](int &end, int &val, bool temp_state){
        end += val * !temp_state;
        val = val * temp_state + temp_state;
    };

    for(; index != stop and !father; index++)
    {
        if(*index > level)
        {
            father = true;
            uf = std::async(one_row, index, stop, level + 1);
        }
        calc(end, val, (level > *index));
    }
    for(; index != stop; index++)
        calc(end, val, (level > *index));

    return (father) ? end + uf.get() : end;
}

int calc(int a, int b)
{
    return a * b;
}

auto speed(const std::vector<int> &input)
{
    std::future<int> f;
    std::time_t start = std::time(nullptr);

    std::cout << calc_rain(input) << std::endl;

    std::time_t ende1 = std::time(nullptr);

    f = std::async(one_row, input.begin(), input.end(), 0);
    std::cout << f.get() << std::endl;

    std::time_t ende2 = std::time(nullptr);
    
    std::time_t exec1 = start - ende1;
    std::time_t exec2 = ende1 - ende2;
    return  exec1 - exec2;
}

auto fill()
{
    std::vector<int> end;
    end.reserve(1000000);
    srand(100);
    for(int i = 0; i < 1000000; i++)
        end.push_back(rand() % 100);
    return end;
}

int main()
{
    std::cout << speed(fill()) << std::endl;
    return 0;
}
