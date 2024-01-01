#ifndef FIELD_PROPERTIES_HPP
#define FIELD_PROPERTIES_HPP

#include "Green.hpp"
#include "LaneProperties.hpp"

#include <utility>
#include <vector>

class FieldProperties : public LaneProperties
{
public:
    // {pos, type}
    using Greens = std::vector<std::pair<unsigned int, Green::Type>>;

    FieldProperties(unsigned int map_width, GameActivity::GameLevel level,
                    LaneProperties const *prev_lane);

    virtual Lane::Type getType() const override;
    virtual std::unique_ptr<Lane> convertToLane() const override;
    Greens const &getGreens() const;

protected:
    virtual void generate() override;
    virtual void setExternalStatic() const override;

private:
    std::vector<unsigned int> findPrevLaneFields() const;

    LaneProperties const *m_prev_lane;
    Greens m_greens;
};

#endif
