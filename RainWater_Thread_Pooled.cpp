#include <iostream>
#include <vector>
#include <mutex>
#include "cryless/cry.h"

int calc_rain1(const std::vector<int> &input)
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

struct Control
{
    int end = 0;
    int val = 0;
    bool temp_state;

    void alter(const bool temp_state)
    {
        end += val * !temp_state;
        val = val * temp_state + temp_state;
    }
};

int calc_rain2(std::vector<int>::const_iterator index, std::vector<int>::const_iterator stop)
{
    cry::Thread_Pool t_pool{4};

    std::vector<std::future<int>> futures;
    int level = 0;
    Control ctrl;

    auto son = [](std::vector<int>::const_iterator index, std::vector<int>::const_iterator stop, const int level){
        Control ctrl;
        for(; index != stop; index++)
            ctrl.alter(level > *index);
        return ctrl.end;
    };

    for(; index != stop; index++)
    {
        for(; level < *index; level++)
            futures.push_back(t_pool.enqueue(
                        [index, level, son, stop] {return son(index, stop, level);}
                        ));
        ctrl.alter(level > *index);
    }
    for(auto &f : futures)
        ctrl.end += f.get();
    return ctrl.end;

}

auto speed(const std::vector<int> &input)
{
    std::future<int> f;
    std::time_t start = std::time(nullptr);

    std::cout << calc_rain1(input) << std::endl;

    std::time_t ende1 = std::time(nullptr);

    std::cout << calc_rain2(input.begin(), input.end()) << std::endl;

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
    //std::vector<int> input{1, 2, 0, 0, 2};
    //std::cout << calc_rain(input.begin(), input.end()) << std::endl;
    //input = {4,2,0,3,2,5};
    //std::cout << "Expected 9: " << calc_rain(input.begin(), input.end()) << std::endl;

    //input = {5,2,0,3,2,5};
    //std::cout << "Expected 13: " << calc_rain(input.begin(), input.end()) << std::endl;

    //input = {6,5,2,0,3,2,5};
    //std::cout << "Expected 13: " << calc_rain(input.begin(), input.end()) << std::endl;

    return 0;
}
