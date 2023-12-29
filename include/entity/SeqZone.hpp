#ifndef SEQ_ZONE_HPP
#define SEQ_ZONE_HPP

#include <Entity.hpp>
#include <Zone.hpp>

class SeqZone: public Entity {
public:
    typedef std::unique_ptr<SeqZone> Ptr;

private:
    std::vector<Zone*> zones;

public:
    SeqZone(Zone::Type type, const sf::Vector2f& size, int numZone);

    Zone* getZone(int index) const;
    void setZoneType(int index, Zone::Type type) const;

    void pushZone(Zone* zone);
    void removeZone(Zone* zone);
    
    Zone::Type getZoneType(int index) const;
    sf::Vector2f getZoneSize();

    virtual int getNearestZoneIndex(ViewGroup* player) const;
    virtual Zone* getNearestZone(ViewGroup* player) const;

    int getNumZone() const;

    ViewGroup::Ptr detachPlayer(ViewGroup* player);
    bool attachPlayer(ViewGroup::Ptr player, Zone* zone);
    bool receivePlayer(ViewGroup* player);
    bool spawnPlayer(ViewGroup::Ptr player);
};

#endif