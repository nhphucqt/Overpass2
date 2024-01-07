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

    float getVehicleVelocity() const;
    float getAnimalVelocity() const;

    bool getHasVehicle() const;
    bool getHasAnimal() const;

protected:
    virtual void generate() override;

private:
    static constexpr float LEVEL_VELOCITIES[][2] = {
        {250.f, 300.f},
        {250.f, 300.f},
        {350.f, 400.f},
        {450.f, 500.f},
        {250.f, 300.f}
    };

    float const mVehicleVelocity, mAnimalVelocity;
    bool hasVehicle, hasAnimal;
    bool m_reverse_p;
};

#endif
