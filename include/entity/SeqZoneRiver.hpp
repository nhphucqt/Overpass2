#ifndef SEQ_ZONE_RIVER_HPP
#define SEQ_ZONE_RIVER_HPP

#include <SeqZone.hpp>

class SeqZoneRiver: public SeqZone {
public:
    typedef std::unique_ptr<SeqZoneRiver> Ptr;

private:
    static const float THRESHOLD;

public:
    SeqZoneRiver(Zone::Type type, sf::Vector2f cellSize, int numZone);
    virtual int getNearestZoneIndex(ViewGroup* player) const override;
    virtual Zone* getNearestZone(ViewGroup* player) const override;
    virtual int getTargetZoneIndex(ViewGroup* player, const sf::Vector2f& dest, float dt) const override;
    virtual Zone* getTargetZone(ViewGroup* player, const sf::Vector2f& dest, float dt) const override;
};

#endif