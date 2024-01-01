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

MapRenderer::MapRenderer(TextureManager const &textures,
                         ViewGroup const &foreground, unsigned int map_width,
                         unsigned int map_max_height,
                         GameActivity::GameLevel level)
    : m_map_generator(new MapGenerator(map_width, map_max_height, level)),
      m_foreground(foreground),
      m_textures(textures)
{
}

void MapRenderer::moveView()
{
    m_map_generator->moveView();
    attachView(convertPropertiesToLane(*m_map_generator->getLanes().back()));
    detachView(*getViews().front());
}

MapRenderer::LaneList MapRenderer::getLanes() const {}

std::unique_ptr<Lane>
MapRenderer::convertPropertiesToLane(LaneProperties const &properties)
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

std::unique_ptr<Lane>
MapRenderer::convertPropertiesToLane(LaneProperties const &properties) const
{
    std::unique_ptr<Field> field;
    return field;
}

std::unique_ptr<Field>
MapRenderer::convertPropertiesToLane(FieldProperties const &properties) const
{
    std::unique_ptr<Field> field;
    return field;
}

std::unique_ptr<Railway>
MapRenderer::convertPropertiesToLane(RailwayProperties const &properties) const
{
    std::unique_ptr<Railway> railway = std::make_unique<Railway>(
        &m_textures, &m_foreground, properties.isReverse());
}

std::unique_ptr<Road>
MapRenderer::convertPropertiesToLane(RoadProperties const &properties) const
{
}

std::unique_ptr<River>
MapRenderer::convertPropertiesToLane(RiverProperties const &properties) const
{
}
