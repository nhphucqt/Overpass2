#include "MapRenderer.hpp"

#include <AppConfig.hpp>
#include <PlayerNode.hpp>
#include <Vector2dUtils.hpp>

PlayerNode::PlayerNode(const TextureManager &textures,
                       std::list<Lane *> const &lanesVct,
                       MapRenderer::LaneList::const_iterator currentLane)
    : sprite(textures.get(TextureID::CharacterIdle)),
      state(State::Idle),
      moveUp(textures.get(TextureID::CharacterUp)),
      moveDown(textures.get(TextureID::CharacterDown)),
      moveLeft(textures.get(TextureID::CharacterLeft)),
      moveRight(textures.get(TextureID::CharacterRight)),
      curLane(currentLane),
      lanes(lanesVct),
      transitionLayer(nullptr),
      lastParent(nullptr),
      __isDead(false)
{
    sf::Vector2f cellSize =
        AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize);
    setSize(cellSize);

    setMoveDuration(sf::seconds(0.2f));

    sprite.setTextureRect(sf::IntRect(0, 0, 14, 16));

    moveUp.setFrameSize(sf::Vector2i(14, 16));
    moveUp.setNumFrames(4);
    moveUp.setDuration(getMoveDuration());

    moveDown.setFrameSize(sf::Vector2i(14, 16));
    moveDown.setNumFrames(4);
    moveDown.setDuration(getMoveDuration());

    moveLeft.setFrameSize(sf::Vector2i(14, 16));
    moveLeft.setNumFrames(4);
    moveLeft.setDuration(getMoveDuration());

    moveRight.setFrameSize(sf::Vector2i(14, 16));
    moveRight.setNumFrames(4);
    moveRight.setDuration(getMoveDuration());

    moveUp.setOrigin(moveUp.getLocalBounds().getSize() / 2.f);
    moveDown.setOrigin(moveDown.getLocalBounds().getSize() / 2.f);
    moveLeft.setOrigin(moveLeft.getLocalBounds().getSize() / 2.f);
    moveRight.setOrigin(moveRight.getLocalBounds().getSize() / 2.f);

    moveUp.setPosition(getBoundingRect().getSize() / 2.f);
    moveDown.setPosition(getBoundingRect().getSize() / 2.f);
    moveLeft.setPosition(getBoundingRect().getSize() / 2.f);
    moveRight.setPosition(getBoundingRect().getSize() / 2.f);

    sprite.scale(5, 5);
    moveUp.scale(5, 5);
    moveDown.scale(5, 5);
    moveLeft.scale(5, 5);
    moveRight.scale(5, 5);
    sprite.setOrigin(sprite.getLocalBounds().getSize() / 2.f);
    sprite.setPosition(getBoundingRect().getSize() / 2.f);
    setHitBox(sprite.getGlobalBounds());
}

void PlayerNode::moveDestination(sf::Vector2f distance)
{
    if (distance.x == 0)
    { // up down
        if (distance.y < 0)
        {
            ++curLane;
        }
        else
        {
            --curLane;
        }
    }
    sf::Vector2f playerPos = getWorldTransform().transformPoint(getOrigin());
    sf::Vector2f dest = playerPos + distance + getAbsoluteVelocity() * getMoveDuration().asSeconds();
    Zone *targetZone =
        (*curLane)->getTargetZone(this, dest, getMoveDuration().asSeconds());
    transitionHandler.setTransition((Entity *)getParent(),
                                    (Entity *)targetZone,
                                    sf::seconds(getMoveDuration().asSeconds()));
    setLastParent(getParent());
    ViewGroup::Ptr thisPtr = getParent()->detachView(*this);
    transitionLayer->attachView(std::move(thisPtr));
}

void PlayerNode::moveDestination(float vx, float vy)
{
    return moveDestination(sf::Vector2f(vx, vy));
}

PlayerNode::State PlayerNode::getState()
{
    return state;
}

void PlayerNode::drawCurrent(sf::RenderTarget &target,
                             sf::RenderStates states) const
{
    if (state == MoveUp)
    {
        target.draw(moveUp, states);
    }
    else if (state == MoveDown)
    {
        target.draw(moveDown, states);
    }
    else if (state == MoveLeft)
    {
        target.draw(moveLeft, states);
    }
    else if (state == MoveRight)
    {
        target.draw(moveRight, states);
    }
    else
    {
        target.draw(sprite, states);
    }

    drawBoundingRect(target, states);
}

void PlayerNode::updateMove(sf::Time delta)
{
    if (!isActionQueueEmpty())
    {
        if (transitionHandler.isFinished())
        {
            sf::Vector2i action = getCurrentAction();
            runAction(action);
            if (action.y < 0 && action.x == 0)
            {
                state = State::MoveUp;
            }
            else if (action.y > 0 && action.x == 0)
            {
                state = State::MoveDown;
            }
            else if (action.x < 0 && action.y == 0)
            {
                state = State::MoveLeft;
            }
            else if (action.x > 0 && action.y == 0)
            {
                state = State::MoveRight;
            }
            else
            {
                state = State::Free;
            }
        }
        if (!transitionHandler.isFinished())
        {
            sf::Vector2f velo =
                ((Entity *)getLastParent())->getAbsoluteVelocity();
            setPosition(transitionHandler.update(delta));
            if (transitionHandler.isFinished())
            {
                if (!(*curLane)->receivePlayer(this))
                {
                    setDead();
                }
                popAction();
                state = State::Idle;
            }
        }
    }
}

void PlayerNode::updateCurrent(sf::Time delta)
{
    updateMove(delta);

    if (state == MoveUp)
    {
        moveUp.update(delta);
        moveUp.setRepeating(true);
    }
    else if (state == MoveDown)
    {
        moveDown.update(delta);
        moveDown.setRepeating(true);
    }
    else if (state == MoveLeft)
    {
        moveLeft.update(delta);
        moveLeft.setRepeating(true);
    }
    else if (state == MoveRight)
    {
        moveRight.update(delta);
        moveRight.setRepeating(true);
    }

    if (state != Idle && state != Free)
    {
        sprite.setTextureRect(sf::IntRect(0, 16 * state, 14, 16));
    }

    Entity::updateCurrent(delta);
}

unsigned int PlayerNode::getCategory() const
{
    return Category::Player;
}

MapRenderer::LaneList::const_iterator PlayerNode::getCurrentLane() const
{
    return curLane;
}

void PlayerNode::moveBack()
{
    sf::Vector2i action = getCurrentAction();
    clearActionQueue();
    pushAction(action);
    if (action.y < 0)
    { // go up
        curLane--;
    }
    else if (action.y > 0)
    {
        curLane++;
    }
    transitionHandler.setIsReversed(true);
}

void PlayerNode::runAction(const sf::Vector2i &direction)
{
    if (direction == sf::Vector2i(0, 0))
    {
        return;
    }

    if (direction.y < 0 && direction.x == 0)
    {
        moveDestination(0, -128);
    }
    else if (direction.y > 0 && direction.x == 0)
    {
        moveDestination(0, 128);
    }
    else if (direction.x < 0 && direction.y == 0)
    {
        moveDestination(-128, 0);
    }
    else if (direction.x > 0 && direction.y == 0)
    {
        moveDestination(128, 0);
    }
}

void PlayerNode::setTransitionLayer(ViewGroup *layer)
{
    transitionLayer = layer;
}

void PlayerNode::setLastParent(ViewGroup *parent)
{
    lastParent = parent;
}

ViewGroup *PlayerNode::getLastParent()
{
    return lastParent;
}

void PlayerNode::pushAction(sf::Vector2i action)
{
    actionQueue.push(action);
}

void PlayerNode::popAction()
{
    actionQueue.pop();
}

sf::Vector2i PlayerNode::getCurrentAction()
{
    return actionQueue.front();
}

bool PlayerNode::isActionQueueEmpty() const
{
    return actionQueue.empty();
}

void PlayerNode::clearActionQueue()
{
    while (!actionQueue.empty())
    {
        actionQueue.pop();
    }
}

void PlayerNode::setMoveDuration(sf::Time duration)
{
    moveDuration = duration;
}

sf::Time PlayerNode::getMoveDuration() const
{
    return moveDuration;
}

void PlayerNode::setDead()
{
    __isDead = true;
}

bool PlayerNode::isDead() const
{
    return __isDead;
}

void PlayerNode::savePlayerData(const std::string &filename)
{
    std::ofstream outf(filename, std::ios::out | std::ios::binary);
    if (outf.is_open())
    {
        PlayerData data;
        data.state = static_cast<int>(state);
        data.curLane = curLane;
        data.onRiver = onRiver;
        data.x = getPosition().x;

        outf.write(reinterpret_cast<const char *>(&data), sizeof(PlayerData));
        outf.close();
    }
    else
    {
        std::runtime_error("PLAYERDATA ERR: " + filename + " cannot be openned.\n");
    }
}

void PlayerNode::loadPlayerData(const std::string &filename)
{
    std::ifstream inf(filename, std::ios::in | std::ios::binary);
    if (inf.is_open())
    {
        PlayerData data;
        inf.read(reinterpret_cast<char *>(&data), sizeof(data));
        inf.close();

        state = static_cast<State>(data.state);
        curLane = data.curLane;
        onRiver = data.onRiver;
        setPosition(data.x, lanes[curLane]->getPosition().y + 24);

        std::cout << "Player spawns at: " << data.x << ' ' << curLane << std::endl;
    }
    else
    {
        std::runtime_error("PLAYERDATA ERR: " + filename + " not found.\n");
    }
}

void PlayerNode::savePlayerData(const std::string &filename)
{
    std::ofstream outf(filename, std::ios::out | std::ios::binary);
    if (outf.is_open())
    {
        PlayerData data;
        data.state = static_cast<int>(state);
        data.curLane = curLane;
        data.onRiver = onRiver;
        data.x = getPosition().x;

        outf.write(reinterpret_cast<const char *>(&data), sizeof(PlayerData));
        outf.close();
    }
    else
    {
        std::runtime_error("PLAYERDATA ERR: " + filename + " cannot be openned.\n");
    }
}

void PlayerNode::loadPlayerData(const std::string &filename)
{
    std::ifstream inf(filename, std::ios::in | std::ios::binary);
    if (inf.is_open())
    {
        PlayerData data;
        inf.read(reinterpret_cast<char *>(&data), sizeof(data));
        inf.close();

        state = static_cast<State>(data.state);
        curLane = data.curLane;
        onRiver = data.onRiver;
        setPosition(data.x, lanes[curLane]->getPosition().y + 24);

        std::cout << "Player spawns at: " << data.x << ' ' << curLane << std::endl;
    }
    else
    {
        std::runtime_error("PLAYERDATA ERR: " + filename + " not found.\n");
    }
}
