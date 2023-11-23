#include "RailProperties.hpp"

RailProperties::RailProperties(int map_width, Level::Type level)
    : LaneProperties(map_width, level)
{
    
}

void RailProperties::generate() const
{
    
}

Lane::Type RailProperties::getType() const
{
    return Lane::Type::Rail;
}
