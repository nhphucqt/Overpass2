#include <SeqZone.hpp>
#include <PlayerNode.hpp>
#include <Vector2dUtils.hpp>
#include <MyRandom.hpp>

SeqZone::SeqZone(Zone::Type type, const sf::Vector2f& size, int numZone) {
    for (int i = 0; i < numZone; i++) {
        Zone::Ptr zone = std::make_unique<Zone>(type, size);
        zone->setPosition(sf::Vector2f(i * size.x, 0));
        attachZone(std::move(zone));
    }
}

Zone* SeqZone::getZone(int index) const {
    return zones[index];
}

void SeqZone::setZoneType(int index, Zone::Type type) const{
    zones[index]->setType(type);
}

void SeqZone::attachZone(Zone::Ptr zone) {
    zones.push_back(zone.get());
    attachView(std::move(zone));
}

void SeqZone::pushZone(Zone* zone) {
    zones.push_back(zone);
}

void SeqZone::removeZone(Zone* zone) {
    auto found = std::find_if(zones.begin(), zones.end(),
    [&] (Zone* p) -> bool { return p == zone; });

    assert(found != zones.end());

    zones.erase(found);
}

Zone::Type SeqZone::getZoneType(int index) const {
    return zones[index]->getType();
}

sf::Vector2f SeqZone::getZoneSize() {
    if (zones.size() == 0)
        return sf::Vector2f(0, 0);
    return zones[0]->getSize();
}

int SeqZone::getNearestZoneIndex(ViewGroup* player) const {
    PlayerNode* playerNode = (PlayerNode*)player;
    sf::Vector2f playerPos = playerNode->getWorldTransform().transformPoint(playerNode->getOrigin());
    int index = 0;
    float minDistance = std::numeric_limits<float>::max();
    for (int i = 0; i < zones.size(); i++) {
        float distance = Vector2dUtils::distance(zones[i]->getCenter(), playerPos);
        if (distance < minDistance) {
            minDistance = distance;
            index = i;
        }
    }
    return index;
}

Zone* SeqZone::getNearestZone(ViewGroup* player) const {
    return zones[getNearestZoneIndex(player)];
}

float SeqZone::getNearestZoneDistance(ViewGroup* player) const {
    PlayerNode* playerNode = (PlayerNode*)player;
    sf::Vector2f playerPos = playerNode->getWorldTransform().transformPoint(playerNode->getOrigin());
    return Vector2dUtils::distance(getNearestZone(player)->getCenter(), playerPos);
}

int SeqZone::getTargetZoneIndex(ViewGroup* player, const sf::Vector2f& dest, float dt) const {
    PlayerNode* playerNode = (PlayerNode*)player;
    int idx = -1;
    float minDistance = std::numeric_limits<float>::max();
    for (int i = 0; i < zones.size(); i++) {
        float distance = Vector2dUtils::distance(zones[i]->getCenter() + zones[i]->getAbsoluteVelocity() * dt, dest);
        if (idx == -1 || distance < minDistance) {
            minDistance = distance;
            idx = i;
        }
    }
    return idx;
}

Zone* SeqZone::getTargetZone(ViewGroup* player, const sf::Vector2f& dest, float dt) const {
    return zones[getTargetZoneIndex(player, dest, dt)];
}

int SeqZone::getNumZone() const {
    return zones.size();
}

ViewGroup::Ptr SeqZone::detachPlayer(ViewGroup* player) {
    ViewGroup* parent = player->getParent();
    ViewGroup::Ptr res = parent->detachView(*player);
    return std::move(res);
}

bool SeqZone::attachPlayer(ViewGroup::Ptr player, Zone* zone) {
    PlayerNode* playerView = (PlayerNode*)player.get();
    zone->attachView(std::move(player));
    return zone->isSafe();
}

bool SeqZone::receivePlayer(ViewGroup* player) {
    Zone* desZone = getNearestZone(player);
    ViewGroup* parent = player->getParent();
    player->setPosition(desZone->getSize() / 2.f);
    ViewGroup::Ptr res = parent->detachView(*player);
    return attachPlayer(std::move(res), desZone);
}

bool SeqZone::spawnPlayer(ViewGroup::Ptr player, int index) {
    Zone* desZone = zones[index];
    player->setPosition(desZone->getSize() / 2.f);
    return attachPlayer(std::move(player), desZone);
}

bool SeqZone::spawnPlayer(ViewGroup::Ptr player) {
    int index = MyRandom::random_range(zones.size());
    return spawnPlayer(std::move(player), index);   
}