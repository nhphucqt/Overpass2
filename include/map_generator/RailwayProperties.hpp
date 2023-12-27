#ifndef RAIL_PROPERTIES_HPP
#define RAIL_PROPERTIES_HPP

#include "LaneProperties.hpp"

class RailwayProperties : public LaneProperties
{
public:
    RailwayProperties(int map_width, GameActivity::GameLevel level);

    virtual void generate() override;
    virtual Lane::Type getType() const override;
    virtual void setExternalStatic() const override;
    bool isReverse() const;

private:
    using LaneProperties::m_level;

    bool m_reverse_p;
};

#endif
