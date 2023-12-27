#include "RoadProperties.hpp"

RoadProperties::RoadProperties(int map_width, GameActivity::GameLevel level)
    : LaneProperties(map_width, level),
      m_vehicles_cnt(LEVEL_VEHICLES_CNTS[static_cast<unsigned int>(level)]),
      m_velocity(LEVEL_VELOCITIES[static_cast<unsigned int>(level)])
{
}

void RoadProperties::generate()
{
    m_reverse_p = LaneUtils::random_range(0, 1);
}

Lane::Type RoadProperties::getType() const
{
    return Lane::Type::Road;
}

void RoadProperties::setExternalStatic() const {}

bool RoadProperties::isReverse() const
{
    return m_reverse_p;
}

unsigned int RoadProperties::getVehiclesCnt() const
{
    return m_vehicles_cnt;
}

float RoadProperties::getVelocity() const
{
    return m_velocity;
}
