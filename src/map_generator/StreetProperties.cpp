#include <cstdlib>

#include "StreetProperties.hpp"

const int StreetProperties::MAX_CAR_WIDTH = 2;
const int StreetProperties::MAX_CARS_DISTANCE = 4;

StreetProperties::StreetProperties(int map_width, Level::Type level)
    : LaneProperties(map_width, level)
{
    
}

void StreetProperties::generate()
{
    m_car_width = std::rand() % MAX_CAR_WIDTH + 1;
    m_cars_distance = std::rand() % MAX_CARS_DISTANCE + 1;
}

Lane::Type StreetProperties::getType() const
{
    return Lane::Type::Street;
}
