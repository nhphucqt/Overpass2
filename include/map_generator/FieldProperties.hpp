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

    FieldProperties(unsigned int map_width, unsigned int level,
                    LaneProperties const *prev_lane, bool initializing_p);

    virtual Lane::Type getType() const override;
    Greens const &getGreens() const;

protected:
    virtual void generate() override;

private:
    unsigned int generateFieldSlot() const;
    std::vector<unsigned int> findPrevLaneFields() const;

    LaneProperties const *m_prev_lane;
    bool const m_initialing_p;
    Greens m_greens;
};

#endif
