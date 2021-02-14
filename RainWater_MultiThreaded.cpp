//https://leetcode.com/problems/trapping-rain-water/
#include <iostream>
#include <tuple>
#include <bits/stdc++.h>
#include <vector>
#include "cryless/cry.h"
#include <thread>
#include <string>

void one_row(const std::vector<int> &input, std::vector<int>::const_iterator index, std::vector<int>::const_iterator stop, int level)
{
    bool flag = false;
    int val = 0;
    int end = 0;
    for(; index != stop; index++)
    {
        if(!flag and *index >= level)
        {
            val = 0;
            end = 0;
            flag = true;
        }
        if(*index < level)
            val++;
        else if(flag)
        {
            end += val;
            val = 0;
        }
    }
    std::cout << "Level " + std::to_string(level) + ": " + std::to_string(end) << std::endl;
}

int calc(int a, int b)
{
    return a * b;
}

int main()
{
    const std::vector<int> input{0,1,0,2,1,0,1,3,2,1,2,1};
    std::vector<std::thread> ts;
    for(int i = 1; i <= 3; i++)
       ts.push_back(std::thread{one_row, input, input.begin(), input.end(), i});
    for(int i = 0; i < 3; i++)
        ts[i].join();

    //input = {4,2,0,3,2,5};
    //std::cout << "Expected 9: " << calc_rain(input) << std::endl;

    //input = {5,2,0,3,2,5};
    //std::cout << "Expected 13: " << calc_rain(input) << std::endl;

    //input = {6,5,2,0,3,2,5};
    //std::cout << "Expected 13: " << calc_rain(input) << std::endl;

    return 0;
}
