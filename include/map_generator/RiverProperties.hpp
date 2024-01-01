#ifndef RIVER_PROPERTIES_HPP
#define RIVER_PROPERTIES_HPP

#include "LaneProperties.hpp"
#include "Log.hpp"
#include "River.hpp"

class RiverProperties : public LaneProperties
{
public:
    RiverProperties(unsigned int map_width, GameActivity::GameLevel level);

    virtual Lane::Type getType() const override;
    virtual std::unique_ptr<Lane> convertToLane() const override;
    bool isReverse() const;
    float getVelocity() const;
    Log::Type getLogType() const;

protected:
    virtual void generate() override;
    virtual void setExternalStatic() const override;

private:
    static constexpr float LEVEL_VELOCITIES[] = {200.f, 250.f, 300.f};

    using LaneProperties::m_level;
    using LaneProperties::m_width;

    bool m_reverse_p;
    float const m_velocity;
    Log::Type m_log_type;
};

#endif
