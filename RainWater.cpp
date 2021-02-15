//https://leetcode.com/problems/trapping-rain-water/
#include <iostream>
#include <tuple>
#include <bits/stdc++.h>
#include <vector>
#include "cryless/cry.h"

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

int main()
{
    std::vector<int> input{0,1,0,2,1,0,1,3,2,1,2,1};
    std::cout << "Expected 6: " << calc_rain(input) << std::endl;

    input = {4,2,0,3,2,5};
    std::cout << "Expected 9: " << calc_rain(input) << std::endl;

    input = {5,2,0,3,2,5};
    std::cout << "Expected 13: " << calc_rain(input) << std::endl;

    input = {6,5,2,0,3,2,5};
    std::cout << "Expected 13: " << calc_rain(input) << std::endl;

    return 0;
}
