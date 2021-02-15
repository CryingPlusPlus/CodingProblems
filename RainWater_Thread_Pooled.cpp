#include <iostream>
#include <vector>
#include <mutex>
#include "cryless/cry.h"


void calc_rain()
{
    void one_row(std::vector<int>::const_iterator index, std::vector<int>::const_iterator stop, int level)
    {
        int temp_end = 0;
        int val = 0;
        int temp_state;
        for(; index != stop; index++)
        {
            {
                std::unique_lock<std::mutex> lock{Event_Mutex};
                for(; max_height <= *index; max_height++)
                {
                    futures.push_back(
                            t_pool.enqueue([this, index, stop] {
                                return one_row(index, stop, max_height);
                                })
                            );
                }
            }
            temp_state = (level > *index);
            temp_end += val * !temp_state;
            val = val * temp_state + temp_state;
        }

    }

    for(int i = 1; i <= 3; i++)
        futures.push_back(
                t_pool.enqueue( [this, i] {
                        return one_row(input.begin(), input.end(), i);
                    })
                );
}


int main()
{
    std::vector<int> input{1, 2, 0, 0, 2};
    int end;
    {
        end = Wrapper Calc{input};
    }
    std::cout << end << std::endl;
    //input = {4,2,0,3,2,5};
    //std::cout << "Expected 9: " << calc_rain(input) << std::endl;

    //input = {5,2,0,3,2,5};
    //std::cout << "Expected 13: " << calc_rain(input) << std::endl;

    //input = {6,5,2,0,3,2,5};
    //std::cout << "Expected 13: " << calc_rain(input) << std::endl;

    return 0;
}
