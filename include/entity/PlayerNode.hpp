#ifndef PLAYERNODE_HPP
#define PLAYERNODE_HPP

#include "MapRenderer.hpp"

#include <Animation.hpp>
#include <Entity.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <TransitionHandler.hpp>
#include <list>

class Lane;

class PlayerNode : public Entity
{
public:
    typedef std::unique_ptr<PlayerNode> Ptr;

    enum State
    {
        MoveDown,
        MoveUp,
        MoveLeft,
        MoveRight,
        Idle,
        Mounted,
        Free
    };
    PlayerNode(const TextureManager &textures, std::list<Lane *> const &lanes,
               MapRenderer::LaneList::const_iterator currentLane, bool isLoad = false, bool isLoad = false);
    void moveDestination(sf::Vector2f distance);
    void moveDestination(float vx, float vy);
    State getState();
    unsigned int getCategory() const;
    MapRenderer::LaneList::const_iterator getCurrentLane() const;
    void moveBack();

    void runAction(const sf::Vector2i &direction);

    void setTransitionLayer(ViewGroup *layer);

    void setLastParent(ViewGroup *parent);
    ViewGroup *getLastParent();

    void pushAction(sf::Vector2i action);
    void popAction();
    sf::Vector2i getCurrentAction();
    bool isActionQueueEmpty() const;
    void clearActionQueue();

    void setMoveDuration(sf::Time duration);
    sf::Time getMoveDuration() const;

    void setDead();
    bool isDead() const;

private:
    virtual void drawCurrent(sf::RenderTarget &target,
                             sf::RenderStates states) const;
    void updateCurrent(sf::Time delta);
    void updateMove(sf::Time delta);

private:
    State state;
    MapRenderer::LaneList::const_iterator curLane;
    MapRenderer::LaneList const &lanes;
    sf::Sprite sprite;
    Animation moveUp;
    Animation moveDown;
    Animation moveLeft;
    Animation moveRight;
    TransitionHandler transitionHandler;
    ViewGroup *transitionLayer;
    ViewGroup *lastParent;
    std::queue<sf::Vector2i> actionQueue;
    sf::Time moveDuration;
    bool __isDead;
    bool onRiver;

private:
    struct PlayerData
    {
        int state;
        bool onRiver;
        float x;
    };

public:
    void savePlayerData(const std::string &filename);
    void loadPlayerData(const std::string &filename);
};

#endif
