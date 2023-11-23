#include "StreetProperties.hpp"

StreetProperties::StreetProperties(int map_width, Level::Type level)
    : LaneProperties(map_width, level)
{
    
}

Lane::Type StreetProperties::getType() const
{
    return Lane::Type::Street;
}
