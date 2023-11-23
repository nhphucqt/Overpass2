#include "RiverProperties.hpp"

RiverProperties::RiverProperties(int map_width, Level::Type level)
    : LaneProperties(map_width, level),
      m_cells(map_width)
{
    
}

Lane::Type RiverProperties::getType() const
{
    return Lane::Type::River;
}
