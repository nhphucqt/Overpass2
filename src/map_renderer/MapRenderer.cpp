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
                         GameActivity::GameLevel level)
    : m_map_generator(
        std::make_unique<MapGenerator>(map_width, map_max_height, level)),
      m_foreground(foreground),
      m_textures(textures)
{
    initialize();
}

void MapRenderer::moveView()
{
    m_map_generator->moveView();
    pushLane();
    popLane();
}

MapRenderer::LaneList const &MapRenderer::getLanes() const
{
    return m_lanes;
}

void MapRenderer::initialize()
{
    auto lanes_properties = m_map_generator->getLanes();
    for (auto it = lanes_properties.begin(); it != lanes_properties.end(); ++it)
    {
        m_lanes.push_back(convertPropertiesToLane(**it).get());
    }
}

void MapRenderer::pushLane()
{
    m_lanes.push_back(
        convertPropertiesToLane(*m_map_generator->getLanes().back()).get());
    attachView(std::unique_ptr<Lane>(m_lanes.back()));
}

void MapRenderer::popLane()
{
    detachView(*m_lanes.front());
    m_lanes.pop_front();
}

std::unique_ptr<Lane>
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

std::unique_ptr<Field>
MapRenderer::convertPropertiesToLane(FieldProperties const &properties) const
{
    auto field = std::make_unique<Field>(&m_textures);
    return field;
}

std::unique_ptr<Railway>
MapRenderer::convertPropertiesToLane(RailwayProperties const &properties) const
{
    return std::make_unique<Railway>(&m_textures, &m_foreground,
                                     properties.isReverse());
}

std::unique_ptr<Road>
MapRenderer::convertPropertiesToLane(RoadProperties const &properties) const
{
    auto road = std::make_unique<Road>(&m_textures, properties.isReverse());
    road->setVehicleVelocity(properties.getVelocity());
    road->setAnimalVelocity(properties.getVelocity());
    road->setNumOfVehicle(properties.getVehiclesCnt());
    road->setNumOfAnimal(properties.getAnimalsCnt());
    return road;
}

std::unique_ptr<River>
MapRenderer::convertPropertiesToLane(RiverProperties const &properties) const
{
    auto river = std::make_unique<River>(&m_textures, properties.isReverse());
    river->setLogVelocity(properties.getVelocity());
    return river;
}
