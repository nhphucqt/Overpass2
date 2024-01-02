#ifndef RAILWAY_PROPERTIES_HPP
#define RAILWAY_PROPERTIES_HPP

#include "LaneProperties.hpp"

#include <memory>

class RailwayProperties : public LaneProperties
{
public:
    RailwayProperties(unsigned int map_width, unsigned int level);

    virtual Lane::Type getType() const override;
    bool isReverse() const;

protected:
    virtual void generate() override;

private:
    bool m_reverse_p;
};

#endif
