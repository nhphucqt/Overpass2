#ifndef MY_RANDOM_HPP
#define MY_RANDOM_HPP

#include <cassert>
#include <random>
#include <algorithm>

class MyRandom {
public:
    static float random_float();
    static float random_float(float l, float r);
    static unsigned int random_range(unsigned int l, unsigned int r);
    static unsigned int random_range(unsigned int r);
    static std::vector<unsigned int> sample(unsigned int n, unsigned int l, unsigned int r);
    static std::vector<unsigned int> sample(unsigned int n, unsigned int r);
    static std::vector<int> sample(unsigned int n, const std::vector<int>& v);
};

#endif