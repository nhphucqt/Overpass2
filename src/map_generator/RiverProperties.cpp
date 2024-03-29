#include "RiverProperties.hpp"

#include "LaneProperties.hpp"
#include <MyRandom.hpp>

RiverProperties::RiverProperties(unsigned int map_width, unsigned int level)
    : LaneProperties(map_width, level),
      m_velocity(MyRandom::random_float(
        LEVEL_VELOCITIES[static_cast<unsigned int>(level)][0],
        LEVEL_VELOCITIES[static_cast<unsigned int>(level)][1])
      )
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

Log::Type RiverProperties::getLogType() const
{
    return m_log_type;
}

void RiverProperties::generate()
{
    m_reverse_p = MyRandom::random_range(0, 1);
    m_log_type = static_cast<Log::Type>(MyRandom::random_range(
        0, static_cast<unsigned int>(Log::Type::Count) - 1));
}
