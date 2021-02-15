#include "cryless/cry.h"
#include <vector>
#include <future>

int mult(int a, int b)
{
    return a * b;
}

int main()
{
    std::vector<int> vec{2, 4, 6, 8};
    std::vector<std::future<int>> result;
    result.reserve(vec.size());

    cry::Thread_Pool pool{std::thread::hardware_concurrency()};

    for(auto el : vec)
        result.push_back( pool.enqueue( [] {
                    return mult(2, el);
                    } ) );
    return 0;
}
