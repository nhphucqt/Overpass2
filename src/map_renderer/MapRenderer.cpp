#include "MapRenderer.hpp"

#include "Field.hpp"
#include "FieldProperties.hpp"
#include "LaneProperties.hpp"
#include "MapGenerator.hpp"
#include "Railway.hpp"
#include "RailwayProperties.hpp"
#include "River.hpp"
#include "RiverProperties.hpp"
#include "Road.hpp"
#include "RoadProperties.hpp"

#include <memory>

MapRenderer::MapRenderer(TextureManager &textures, ViewGroup &foreground,
                         unsigned int map_width, unsigned int map_max_height,
                         unsigned int level)
    : m_map_generator(
        std::make_unique<MapGenerator>(map_width, map_max_height, level)),
      m_foreground(foreground),
      m_textures(textures)
{
    initialize();
}

void MapRenderer::moveView()
{
    if (m_lanes.size() < 10)
    {
        return;
    }

    m_map_generator->moveView();
    popLane();
    pushLane();
}

MapRenderer::LaneList const &MapRenderer::getLanes() const
{
    return m_lanes;
}

void MapRenderer::initialize()
{
    auto const &lanes_properties = m_map_generator->getLanes();
    for (auto it = lanes_properties.begin(); it != lanes_properties.end(); ++it)
    {
        m_lanes.push_back(convertPropertiesToLane(**it));
    }
}

void MapRenderer::pushLane()
{
    m_lanes.push_back(
        convertPropertiesToLane(*m_map_generator->getLanes().back()));
}

void MapRenderer::popLane()
{
    m_lanes.pop_front();
}

Lane *
MapRenderer::convertPropertiesToLane(LaneProperties const &properties) const
{
    switch (properties.getType())
    {
    case Lane::Type::Field:
        return convertPropertiesToLane(
            dynamic_cast<FieldProperties const &>(properties));

    case Lane::Type::Railway:
        return convertPropertiesToLane(
            dynamic_cast<RailwayProperties const &>(properties));

    case Lane::Type::Road:
        return convertPropertiesToLane(
            dynamic_cast<RoadProperties const &>(properties));

    case Lane::Type::River:
        return convertPropertiesToLane(
            dynamic_cast<RiverProperties const &>(properties));

    default:
        return nullptr;
    }
}

Field *
MapRenderer::convertPropertiesToLane(FieldProperties const &properties) const
{
    auto field = new Field(&m_textures);
    for (auto const &[index, green_type] : properties.getGreens())
    {
        auto green = std::make_unique<Green>(green_type, m_textures);
        field->add(std::move(green), index);
    }
    return field;
}

Railway *
MapRenderer::convertPropertiesToLane(RailwayProperties const &properties) const
{
    return new Railway(&m_textures, &m_foreground, properties.isReverse());
}

Road *
MapRenderer::convertPropertiesToLane(RoadProperties const &properties) const
{
    auto road = new Road(
        &m_textures, properties.isReverse(), properties.getVehiclesCnt(),
        properties.getAnimalsCnt(), properties.getVehicleType(),
        properties.getAnimalType(), properties.getVelocity());
    return road;
}

River *
MapRenderer::convertPropertiesToLane(RiverProperties const &properties) const
{
    auto river = new River(&m_textures, properties.isReverse(),
                           properties.getVelocity());
    river->setLogVelocity(properties.getVelocity());
    return river;
}
