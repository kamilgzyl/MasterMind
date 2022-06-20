#pragma once
#include <random>

namespace MM
{
class RandomGenerator
{
    public:
    static int generateNumber(unsigned startValue, unsigned endValue)
    {
        std::random_device r;

        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(startValue, endValue - 1);
        return uniform_dist(e1);
    }
};
} //namespace MM