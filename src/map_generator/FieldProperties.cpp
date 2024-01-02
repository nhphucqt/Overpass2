#include "FieldProperties.hpp"

#include "Field.hpp"
#include "LaneProperties.hpp"

#include <climits>

FieldProperties::FieldProperties(unsigned int map_width, unsigned int level,
                                 LaneProperties const *prev_lane)
    : LaneProperties(map_width, level),
      m_prev_lane(prev_lane)
{
}

Lane::Type FieldProperties::getType() const
{
    return Lane::Type::Field;
}

FieldProperties::Greens const &FieldProperties::getGreens() const
{
    return m_greens;
}

void FieldProperties::generate()
{
    unsigned int green_cnt = LaneUtils::random_range(0, m_width - 1);

    unsigned int field_slot = UINT_MAX;
    if (m_prev_lane && m_prev_lane->getType() == Lane::Type::Field)
    {
        std::vector<unsigned int> prev_lane_fields = findPrevLaneFields();
        field_slot = prev_lane_fields[LaneUtils::random_range(
            0, prev_lane_fields.size() - 1)];
    }

    unsigned int lbound = 0;
    unsigned int rbound = m_width - green_cnt - (field_slot < m_width);
    for (int i = 1; i <= green_cnt; ++i)
    {
        unsigned int green_type = LaneUtils::random_range(
            0, static_cast<unsigned int>(Green::Type::Count) - 1);
        unsigned int green_slot = LaneUtils::random_range(lbound, rbound);
        m_greens.emplace_back(green_slot, static_cast<Green::Type>(green_type));

        lbound = green_slot + 1;
        ++rbound;
    }
    for (auto &[index, green] : m_greens)
    {
        index += (index >= field_slot);
    }
}

std::vector<unsigned int> FieldProperties::findPrevLaneFields() const
{
    std::vector<unsigned int> prev_lane_fields;
    Greens const &prev_lane_greens =
        dynamic_cast<FieldProperties const *>(m_prev_lane)->m_greens;

    int i = 0, j = 0;
    while (i < prev_lane_greens.size())
    {
        while (j < prev_lane_greens[i].first)
        {
            prev_lane_fields.push_back(j++);
        }
        ++i;
        ++j;
    }
    while (j < m_width)
    {
        prev_lane_fields.push_back(j++);
    }
    return prev_lane_fields;
}
