#include "PavementProperties.hpp"

PavementProperties::PavementProperties(int map_width, Level::Type level)
    : LaneProperties(map_width, level),
      m_cells(map_width)
{
    
}

Lane::Type PavementProperties::getType() const
{
    return Lane::Type::Pavement;
}
