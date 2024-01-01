#ifndef RAILWAY_PROPERTIES_HPP
#define RAILWAY_PROPERTIES_HPP

#include "LaneProperties.hpp"

#include <memory>

class RailwayProperties : public LaneProperties
{
public:
    RailwayProperties(unsigned int map_width, GameActivity::GameLevel level);

    virtual Lane::Type getType() const override;
    virtual std::unique_ptr<Lane> convertToLane() const override;
    bool isReverse() const;

protected:
    virtual void generate() override;
    virtual void setExternalStatic() const override;

private:
    bool m_reverse_p;
};

#endif
