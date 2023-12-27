#ifndef STREET_PROPERTIES_HPP
#define STREET_PROPERTIES_HPP

#include "GameActivity.hpp"
#include "LaneProperties.hpp"

class RoadProperties : public LaneProperties
{
public:
    RoadProperties(unsigned int map_width, GameActivity::GameLevel level);

    virtual void generate() override;
    virtual Lane::Type getType() const override;
    virtual void setExternalStatic() const override;
    bool isReverse() const;
    unsigned int getVehiclesCnt() const;
    unsigned int getAnimalsCnt() const;
    float getVelocity() const;

private:
    static constexpr float LEVEL_VELOCITIES[] = {300.f, 350.f, 400.f};
    static constexpr unsigned int LEVEL_VEHICLES_CNTS[] = {3, 4, 5};
    static constexpr unsigned int LEVEL_ANIMALS_CNT[] = {2, 3, 4};

    using LaneProperties::m_level;
    using LaneProperties::m_width;

    unsigned int const m_vehicles_cnt;
    unsigned int const m_animals_cnt;
    float const m_velocity;
    bool m_reverse_p, m_has_animal_p;
};

#endif
