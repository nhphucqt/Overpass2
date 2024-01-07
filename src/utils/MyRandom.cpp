// Reference: https://en.wikipedia.org/wiki/Reservoir_sampling

#include <MyRandom.hpp>

float MyRandom::random_float() {
    return (float)std::rand() / RAND_MAX;
}

float MyRandom::random_float(float l, float r) {
    assert(l <= r);
    return random_float() * (r - l) + l;
}

unsigned int MyRandom::random_range(unsigned int l, unsigned int r) {
    assert(l <= r);
    return std::rand() % (r - l + 1) + l;
}

unsigned int MyRandom::random_range(unsigned int r) {
    assert(r > 0);
    return std::rand() % r;
}

std::vector<unsigned int> MyRandom::sample(unsigned int n, unsigned int l, unsigned int r) {
    assert(n <= r - l + 1);
    std::vector<unsigned int> res;
    if (n == 0) return res;
    for (int i = l; i < l+n; ++i) {
        res.push_back(i);
    }
    for (int i = l+n; i <= r; ++i) {
        int j = random_range(i);
        if (j < n) {
            res[j] = i;
        }
    }
    return res;
}

std::vector<unsigned int> MyRandom::sample(unsigned int n, unsigned int r) {
    assert(n <= r);
    return sample(n, 0, r-1);
}

std::vector<int> MyRandom::sample(unsigned int n, const std::vector<int>& v) {
    assert(n <= v.size());
    std::vector<int> res;
    if (n == 0) return res;
    if (n == (int)v.size()) return v;
    for (int i = 0; i < n; ++i) {
        res.push_back(v[i]);
    }
    for (int i = n; i < v.size(); ++i) {
        int j = random_range(i);
        if (j < n) {
            res[j] = v[i];
        }
    }
    return res;
}

