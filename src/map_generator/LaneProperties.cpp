#include "LaneProperties.hpp"

LaneProperties::LaneProperties(unsigned int map_width, unsigned int level)
    : m_width(map_width),
      m_level(level)
{
}

void LaneProperties::create()
{
    generate();
}
