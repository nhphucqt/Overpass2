#ifndef PAVEMENT_PROPERTIES_HPP
#define PAVEMENT_PROPERTIES_HPP

#include "Green.hpp"
#include "LaneProperties.hpp"

#include <utility>
#include <vector>

class FieldProperties : public LaneProperties
{
public:
    // {pos, type}
    using Greens = std::vector<std::pair<unsigned int, Green::Type>>;

    FieldProperties(int map_width, GameActivity::GameLevel level,
                    LaneProperties const *prev_lane = nullptr);

    virtual void generate() override;
    virtual Lane::Type getType() const override;
    virtual void setExternalStatic() const override;
    Greens const &getGreens() const;

private:
    using LaneProperties::m_level;
    using LaneProperties::m_width;

    std::vector<unsigned int> find_prev_lane_fields();

    LaneProperties const *m_prev_lane;
    Greens m_greens;
};

#endif
