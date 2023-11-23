#ifndef RAIL_PROPERTIES_HPP
#define RAIL_PROPERTIES_HPP

#include "LaneProperties.hpp"

class RailProperties : public LaneProperties
{
public:
    RailProperties(int map_width, Level::Type level);
    
    virtual void generate();
    virtual Lane::Type getType() const override;

private:
    using LaneProperties::m_level;
};

#endif
