#ifndef ROAD_PROPERTIES_HPP
#define ROAD_PROPERTIES_HPP

#include "Animal.hpp"
#include "LaneProperties.hpp"
#include "Vehicle.hpp"

#include <memory>

class RoadProperties : public LaneProperties
{
public:
    RoadProperties(unsigned int map_width, unsigned int level);

    virtual Lane::Type getType() const override;
    bool isReverse() const;
    float getVelocity() const;
    unsigned int getVehiclesCnt() const;
    unsigned int getAnimalsCnt() const;
    Animal::Type getAnimalType() const;
    Vehicle::Type getVehicleType() const;

protected:
    virtual void generate() override;

private:
    static constexpr float LEVEL_VELOCITIES[] = {300.f, 400.f, 500.f};
    static constexpr unsigned int LEVEL_VEHICLES_CNTS[] = {3, 4, 5};
    static constexpr unsigned int LEVEL_ANIMALS_CNTS[] = {1, 2, 3};

    unsigned int const m_vehicles_cnt;
    unsigned int const m_animals_cnt;
    float const m_velocity;
    bool m_reverse_p, m_has_animal_p;
    Animal::Type m_animal_type;
    Vehicle::Type m_vehicle_type;
};

#endif
