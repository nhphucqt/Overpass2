#include <Lane.hpp>
#include <AppConfig.hpp>

Lane::Lane(const sf::Texture &texture, TextureHolder *textures, bool reverse): sprite(texture), laneTextures(textures), isReverse(reverse) {
    AppConfig& config = AppConfig::getInstance();
    int numLaneCells = config.get<int>(ConfigKey::NumLaneCells);
    sf::Vector2f cellSize = config.get<sf::Vector2f>(ConfigKey::CellSize);
	sf::IntRect textureRect(0, 0, numLaneCells * int(cellSize.x), (int)cellSize.y);
    sprite.setTextureRect(textureRect);

    SeqZone::Ptr zonePtr = std::make_unique<SeqZone>(Zone::Type::Safe, cellSize, numLaneCells);
    seqZone = zonePtr.get();
    attachView(std::move(zonePtr));
}

sf::FloatRect Lane::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

void Lane::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

bool Lane::receivePlayer(ViewGroup* player) {
    return seqZone->receivePlayer(player);
}

bool Lane::spawnPlayer(ViewGroup::Ptr player, int index) {
    return seqZone->spawnPlayer(std::move(player), index);
}

bool Lane::spawnPlayer(ViewGroup::Ptr player) {
    return seqZone->spawnPlayer(std::move(player));
}

float Lane::getNearestDistance(ViewGroup* player) const {
    return seqZone->getNearestZoneDistance(player);
}   

Zone* Lane::getTargetZone(ViewGroup* player, const sf::Vector2f& dest, float dt) const {
    return seqZone->getTargetZone(player, dest, dt);
}

unsigned int Lane::getCategory() const {
    return ViewCategory::Lane;
}

bool Lane::isOutofView(Entity *entity, float laneLength) const {
    return (isReverse && entity->getPosition().x + entity->getHitBox().getSize().x < 0)
        || (!isReverse && entity->getPosition().x > laneLength);
}   

bool Lane::isIntoView(Entity *entity, float laneLength) const {
    return (!isReverse && entity->getPosition().x > 0)
        || (isReverse && entity->getPosition().x + entity->getHitBox().getSize().x < laneLength);
}