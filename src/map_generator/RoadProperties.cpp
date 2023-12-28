#include "RoadProperties.hpp"

RoadProperties::RoadProperties(unsigned int map_width,
                               GameActivity::GameLevel level)
    : LaneProperties(map_width, level),
      m_vehicles_cnt(LEVEL_VEHICLES_CNTS[static_cast<unsigned int>(level)]),
      m_animals_cnt(LEVEL_ANIMALS_CNTS[static_cast<unsigned int>(level)]),
      m_velocity(LEVEL_VELOCITIES[static_cast<unsigned int>(level)])
{
}

Lane::Type RoadProperties::getType() const
{
    return Lane::Type::Road;
}

bool RoadProperties::isReverse() const
{
    return m_reverse_p;
}

unsigned int RoadProperties::getVehiclesCnt() const
{
    return m_has_animal_p ? 0 : m_vehicles_cnt;
}

unsigned int RoadProperties::getAnimalsCnt() const
{
    return m_has_animal_p ? m_animals_cnt : 0;
}

Animal::Type RoadProperties::getAminalType() const
{
    return m_animal_type;
}

Vehicle::Type RoadProperties::getVehicleType() const
{
    return m_vehicle_type;
}

float RoadProperties::getVelocity() const
{
    return m_velocity;
}

void RoadProperties::generate()
{
    m_reverse_p = LaneUtils::random_range(0, 1);
    m_has_animal_p = LaneUtils::random_range(0, 1);
    m_animal_type = static_cast<Animal::Type>(LaneUtils::random_range(
        0, static_cast<unsigned int>(Animal::Type::Count) - 1));
    m_vehicle_type = static_cast<Vehicle::Type>(LaneUtils::random_range(
        0, static_cast<unsigned int>(Vehicle::Type::Count) - 1));
}

void RoadProperties::setExternalStatic() const {}
