#include <cstdlib>

#include "RiverProperties.hpp"

RiverProperties::RiverProperties(int map_width, Level::Type level)
    : LaneProperties(map_width, level),
      m_cells(map_width)
{
    
}

void RiverProperties::generate()
{
    
    for (auto &cell : m_cells)
    {
        cell = (std::rand() & 1);
    }
}

Lane::Type RiverProperties::getType() const
{
    return Lane::Type::River;
}
