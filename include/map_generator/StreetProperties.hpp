#ifndef STREET_PROPERTIES_HPP
#define STREET_PROPERTIES_HPP

#include "LaneProperties.hpp"

class StreetProperties : public LaneProperties
{
public:
    StreetProperties(int map_width, Level::Type level);
    
    virtual void generate() override;
    virtual Lane::Type getType() const override;
    int getCarWidth() const;
    int getCarsDistance() const;
    float getVelocity() const;

private:
    static const int MAX_CAR_WIDTH;
    static const int MAX_CARS_DISTANCE;
    static const float LEVEL_VELOCITIES[Level::TYPES_CNT];
    
    using LaneProperties::m_level;
    
    int m_car_width, m_cars_distance;
    float m_velocity;
};

#endif
