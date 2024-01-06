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
    : m_textures(textures),
      m_foreground(foreground),
      m_sizes(map_width, map_max_height),
      m_width(m_sizes.x),
      m_max_height(m_sizes.y),
      m_level(level)
{
    initialize();
}

void MapRenderer::moveView()
{
    // popLane();
    pushLane(0);
}

MapRenderer::LaneList const &MapRenderer::getLanes() const
{
    return m_lanes;
}

void MapRenderer::initialize()
{
    m_map_generator =
        std::make_unique<MapGenerator>(m_width, m_max_height, m_level);
    for (int i = 0; i < m_max_height; ++i)
    {
        pushLane(1);
    }
}

void MapRenderer::pushLane(bool initializing_p)
{
    m_map_generator->moveView(initializing_p);
    m_lanes.push_back(convertPropertiesToLane(m_map_generator->getCurrLane()));
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
    return new Railway(&m_textures, properties.isReverse(), 
                       properties.getTrainInterval(), properties.getTrainDelay(), properties.getTrainOffSet());
}

Road *
MapRenderer::convertPropertiesToLane(RoadProperties const &properties) const
{
    auto road = new Road(
        &m_textures, properties.isReverse(), 
        properties.getVehicleVelocity(), properties.getAnimalVelocity(),
        properties.getHasVehicle(), properties.getHasAnimal()
    );
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
