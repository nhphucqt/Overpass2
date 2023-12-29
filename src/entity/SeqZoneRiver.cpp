#include <SeqZoneRiver.hpp>
#include <Vector2dUtils.hpp>
#include <iostream>

const float SeqZoneRiver::THRESHOLD = 80.f;

SeqZoneRiver::SeqZoneRiver(Zone::Type type, sf::Vector2f cellSize, int numZone): SeqZone(type, cellSize, numZone) {}

int SeqZoneRiver::getNearestZoneIndex(ViewGroup* player) const {
    sf::Vector2f playerPos = player->getWorldTransform().transformPoint(player->getOrigin());
    int index = -1;
    float minDistance = std::numeric_limits<float>::max();
    for (int i = 0; i < getNumZone(); ++i) {
        if (getZoneType(i) == Zone::Type::Safe) {
            if (index == -1 || Vector2dUtils::distance(getZone(i)->getCenter(), playerPos) < minDistance) {
                index = i;
                minDistance = Vector2dUtils::distance(getZone(i)->getCenter(), playerPos);
            }
        }
    }
    return index == -1 || minDistance > THRESHOLD ? SeqZone::getNearestZoneIndex(player) : index;
}

Zone* SeqZoneRiver::getNearestZone(ViewGroup* player) const {
    return getZone(getNearestZoneIndex(player));
}

int SeqZoneRiver::getTargetZoneIndex(ViewGroup* player, const sf::Vector2f& dest, float dt) const {
    sf::Vector2f playerPos = player->getWorldTransform().transformPoint(player->getOrigin());
    int index = -1;
    float minDistance = std::numeric_limits<float>::max();
    for (int i = 0; i < getNumZone(); ++i) {
        if (getZoneType(i) == Zone::Type::Safe) {
            if (index == -1 || Vector2dUtils::distance(getZone(i)->getCenter() + getZone(i)->getAbsoluteVelocity() * dt, dest) < minDistance) {
                index = i;
                minDistance = Vector2dUtils::distance(getZone(i)->getCenter() + getZone(i)->getAbsoluteVelocity() * dt, dest);
            }
        }
    }
    return index == -1 || minDistance > THRESHOLD ? SeqZone::getTargetZoneIndex(player, dest, dt) : index;
}

Zone* SeqZoneRiver::getTargetZone(ViewGroup* player, const sf::Vector2f& dest, float dt) const {
    return getZone(getTargetZoneIndex(player, dest, dt));
}