#include "FieldProperties.hpp"

#include "LaneProperties.hpp"

FieldProperties::FieldProperties(int map_width, GameActivity::GameLevel level,
                                 LaneProperties const *prev_lane)
    : LaneProperties(map_width, level),
      m_prev_lane(prev_lane)
{
}

void FieldProperties::generate()
{
    unsigned int green_cnt = LaneUtils::random_range(0, m_width - 1);
    unsigned int field_slot = -1;
    if (m_prev_lane && m_prev_lane->getType() == Lane::Type::Field)
    {
        std::vector<unsigned int> prev_lane_fields = find_prev_lane_fields();
        field_slot = prev_lane_fields[LaneUtils::random_range(
            0, prev_lane_fields.size() - 1)];
    }
    for (int i = 0; i < green_cnt; ++i)
    {
        unsigned int green_type =
            LaneUtils::random_range(0, Green::GreenTypeCnt);
        unsigned int lbound = (i == 0 ? 0 : m_greens.back().first + 1);
        unsigned int green_slot;
        do
        {
            green_slot = LaneUtils::random_range(lbound, m_width - 1);
        } while (green_slot == field_slot);
        m_greens.emplace_back(green_slot, green_type);
    }

    setExternalStatic();
}

Lane::Type FieldProperties::getType() const
{
    return Lane::Type::Field;
}

FieldProperties::Greens const &FieldProperties::getGreens() const
{
    return m_greens;
}

std::vector<unsigned int> FieldProperties::find_prev_lane_fields()
{
    std::vector<unsigned int> prev_lane_fields;
    Greens const &prev_lane_greens =
        static_cast<FieldProperties const *>(m_prev_lane)->m_greens;

    for (int i = 0; i < prev_lane_greens.size(); ++i)
    {
        unsigned int lbound = (i == 0 ? 0 : prev_lane_greens[i - 1].first + 1);
        for (int j = lbound; j < prev_lane_greens[i].first; ++j)
        {
            prev_lane_fields.push_back(j);
        }
    }
    for (int i = prev_lane_greens.back().first; i < m_width; ++i)
    {
        prev_lane_fields.push_back(i);
    }

    return prev_lane_fields;
}

void FieldProperties::setExternalStatic() const {}
