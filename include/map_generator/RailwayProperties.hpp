#ifndef RAILWAY_PROPERTIES_HPP
#define RAILWAY_PROPERTIES_HPP

#include "LaneProperties.hpp"

class RailwayProperties : public LaneProperties
{
public:
    RailwayProperties(unsigned int map_width, GameActivity::GameLevel level);

    virtual Lane::Type getType() const override;
    bool isReverse() const;

protected:
    virtual void generate() override;
    virtual void setExternalStatic() const override;

private:
    using LaneProperties::m_level;
    using LaneProperties::m_width;

    bool m_reverse_p;
};

#endif
