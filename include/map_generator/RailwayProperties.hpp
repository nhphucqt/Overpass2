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
    float getTrainInterval() const;
    float getTrainDelay() const;
    float getTrainOffSet() const;

protected:
    virtual void generate() override;

private:
    static constexpr float LEVEL_DELAY[][2] = {
        {1.f, 3.f},
        {1.f, 3.f},
        {1.f, 3.f}
    };
    static constexpr float LEVEL_INV[][2] = {
        {5.f, 7.f},
        {5.f, 7.f},
        {5.f, 7.f}
    };
    static constexpr float LEVEL_TRAIN_OFFSET[][2] = {
        {4000.f, 4000.f},
        {3000.f, 3000.f},
        {2000.f, 2000.f}
    };

    bool m_reverse_p;
    float trainInterval;
    float trainDelay;
    float trainOffSet;
};

#endif
