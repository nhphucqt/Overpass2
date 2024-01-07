#include "FieldProperties.hpp"

#include "Field.hpp"
#include "LaneProperties.hpp"

#include <MyRandom.hpp>
#include <climits>

FieldProperties::FieldProperties(unsigned int map_width, unsigned int level,
                                 LaneProperties const *prev_lane,
                                 bool initializing_p, bool spawn_lane_p)
    : LaneProperties(map_width, level),
      m_prev_lane(prev_lane),
      m_initialing_p(initializing_p),
      m_spawn_lane_p(spawn_lane_p)
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
    if (m_spawn_lane_p)
    {
        return;
    }

    unsigned int green_cnt = MyRandom::random_range(0, m_width / 2);
    std::vector<unsigned int> green_slots =
        MyRandom::sample(green_cnt, m_width);
    std::sort(green_slots.begin(), green_slots.end());
    for (auto slot : green_slots)
    {
        unsigned int green_type = MyRandom::random_range(
            0, static_cast<unsigned int>(Green::Type::Count) - 1);
        m_greens.emplace_back(slot, static_cast<Green::Type>(green_type));
    }
}

unsigned int FieldProperties::generateFieldSlot() const
{
    unsigned int field_slot = UINT_MAX;
    if (m_initialing_p)
    {
        field_slot = 0;
    }
    else if (m_prev_lane && m_prev_lane->getType() == Lane::Type::Field)
    {
        std::vector<unsigned int> prev_lane_fields = findPrevLaneFields();
        field_slot = prev_lane_fields[MyRandom::random_range(
            0, prev_lane_fields.size() - 1)];
    }
    return field_slot;
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
