#include "RiverProperties.hpp"

#include "LaneProperties.hpp"

RiverProperties::RiverProperties(unsigned int map_width,
                                 GameActivity::GameLevel level)
    : LaneProperties(map_width, level),
      m_velocity(LEVEL_VELOCITIES[static_cast<unsigned int>(level)])
{
}

Lane::Type RiverProperties::getType() const
{
    return Lane::Type::River;
}

bool RiverProperties::isReverse() const
{
    return m_reverse_p;
}

float RiverProperties::getVelocity() const
{
    return m_velocity;
}

void RiverProperties::generate()
{
    m_reverse_p = LaneUtils::random_range(0, 1);
    m_log_type = static_cast<Log::Type>(LaneUtils::random_range(
        0, static_cast<unsigned int>(Log::Type::Count) - 1));
}

void RiverProperties::setExternalStatic() const {}
