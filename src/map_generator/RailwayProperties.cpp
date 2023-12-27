#include "RailwayProperties.hpp"

#include "Railway.hpp"

RailwayProperties::RailwayProperties(int map_width,
                                     GameActivity::GameLevel level)
    : LaneProperties(map_width, level)
{
}

void RailwayProperties::generate()
{
    m_reverse_p = LaneUtils::random_range(0, 1);
}

Lane::Type RailwayProperties::getType() const
{
    return Lane::Type::Railway;
}

bool RailwayProperties::isReverse() const
{
    return m_reverse_p;
}
