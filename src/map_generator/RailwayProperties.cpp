#include "RailwayProperties.hpp"

#include "Railway.hpp"

#include <memory>

RailwayProperties::RailwayProperties(unsigned int map_width,
                                     GameActivity::GameLevel level)
    : LaneProperties(map_width, level)
{
}

Lane::Type RailwayProperties::getType() const
{
    return Lane::Type::Railway;
}

bool RailwayProperties::isReverse() const
{
    return m_reverse_p;
}

void RailwayProperties::generate()
{
    m_reverse_p = LaneUtils::random_range(0, 1);
}

void RailwayProperties::setExternalStatic() const {}
