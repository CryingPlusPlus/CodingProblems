//https://leetcode.com/problems/trapping-rain-water/
#include <iostream>
#include <tuple>
#include <bits/stdc++.h>
#include <vector>

template <typename T,
          typename TIter = decltype(std::begin(std::declval<T>())),
          typename = decltype(std::end(std::declval<T>()))>
constexpr auto enumerate(T && iterable)
{
    struct iterator
    {
        size_t i;
        TIter iter;
        bool operator != (const iterator & other) const { return iter != other.iter; }
        void operator ++ () {++i; ++iter;}
        auto operator * () const { return std::tie(i, *iter); }
    
    };

    struct iterable_wrapper
    {
        T iterable;
        auto begin() { return iterator{ 0, std::begin(iterable)  };  }
        auto end() { return iterator{ 0, std::end(iterable)  };  }
                                    
    };
    return iterable_wrapper{ std::forward<T>(iterable) };
}

int calc_rain(const std::vector<int> &input)
{
    std::vector<int> levels;
    int end = 0;
    for(auto index : input)
    {
        if(levels.size() <= index)
        {
            for(int i = levels.size(); i < index; i++)
                levels.push_back(0);
        }
        for(auto [i, lvl] : enumerate(levels))
        {
            if(i + 1 > index)
                lvl++;
            else
            {
                end += lvl;
                lvl = 0;
            }
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
