#include "LaneProperties.hpp"

#include <cstdlib>

unsigned int LaneUtils::random_range(int l, int r)
{
    return std::rand() % (r - l + 1) + l;
}

LaneProperties::LaneProperties(int map_width, GameActivity::GameLevel level)
    : m_width(map_width),
      m_level(level)
{
}
