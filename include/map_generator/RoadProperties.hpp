#ifndef ROAD_PROPERTIES_HPP
#define ROAD_PROPERTIES_HPP

#include "Animal.hpp"
#include "GameActivity.hpp"
#include "LaneProperties.hpp"
#include "Vehicle.hpp"

class RoadProperties : public LaneProperties
{
public:
    RoadProperties(unsigned int map_width, GameActivity::GameLevel level);

    virtual Lane::Type getType() const override;
    bool isReverse() const;
    float getVelocity() const;
    unsigned int getVehiclesCnt() const;
    unsigned int getAnimalsCnt() const;
    Animal::Type getAminalType() const;
    Vehicle::Type getVehicleType() const;

protected:
    virtual void generate() override;
    virtual void setExternalStatic() const override;

private:
    static constexpr float LEVEL_VELOCITIES[] = {300.f, 350.f, 400.f};
    static constexpr unsigned int LEVEL_VEHICLES_CNTS[] = {3, 4, 5};
    static constexpr unsigned int LEVEL_ANIMALS_CNTS[] = {2, 3, 4};

    using LaneProperties::m_level;
    using LaneProperties::m_width;

    unsigned int const m_vehicles_cnt;
    unsigned int const m_animals_cnt;
    float const m_velocity;
    bool m_reverse_p, m_has_animal_p;
    Animal::Type m_animal_type;
    Vehicle::Type m_vehicle_type;
};

#endif
