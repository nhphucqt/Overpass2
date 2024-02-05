#include "MapRenderer.hpp"

#include <TextView.hpp>

#include <AppConfig.hpp>
#include <PlayerNode.hpp>
#include <Vector2dUtils.hpp>

const float PlayerNode::MOVE_DURATION = 0.2f;
const float PlayerNode::SLOW_MOVE_DURATION = 0.3f;

PlayerNode::PlayerNode(ViewCategory::Type type, const TextureHolder &textures,
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
      __isDead(false),
      currentScore(0),
      currentDistance(0),
      mCategory(type)
{
    sf::Vector2f cellSize =
        AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize);
    setSize(cellSize);

    setMoveDuration(MOVE_DURATION);

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

PlayerNode::PlayerNode(ViewCategory::Type type, const TextureHolder &textures, std::list<Lane *> const &lanesVct)
: PlayerNode(type, textures, lanesVct, lanesVct.begin()) {}

PlayerNode::PlayerNode(const TextureHolder &textures, std::list<Lane *> const &lanesVct, MapRenderer::LaneList::const_iterator currentLane)
: PlayerNode(ViewCategory::Player_1, textures, lanesVct, currentLane) {}

PlayerNode::PlayerNode(const TextureHolder &textures, std::list<Lane *> const &lanesVct)
: PlayerNode(textures, lanesVct, lanesVct.begin()) {}

void PlayerNode::moveDestination(sf::Vector2f distance) {
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
    setLastParent((Entity*)getParent());
    ViewGroup::Ptr thisPtr = getParent()->detachView(*this);
    transitionLayer->attachView(std::move(thisPtr));
}

void PlayerNode::moveDestination(float vx, float vy) {
    return moveDestination(sf::Vector2f(vx, vy));
}

PlayerNode::State PlayerNode::getState() {
    return state;
}

void PlayerNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    switch(state) {
        case State::MoveUp:
            target.draw(moveUp, states);
            break;
        case State::MoveDown:
            target.draw(moveDown, states);
            break;
        case State::MoveLeft:
            target.draw(moveLeft, states);
            break;
        case State::MoveRight:
            target.draw(moveRight, states);
            break;
        default:
            target.draw(sprite, states);
    }
    drawBoundingRect(target, states);
}

void PlayerNode::updateMove(sf::Time delta) {
    if (!isActionQueueEmpty()) {
        if (transitionHandler.isFinished()) {
            sf::Vector2i action = getCurrentAction();
            runAction(action);
            if (action.y < 0 && action.x == 0) {
                state = State::MoveUp;
            } else if (action.y > 0 && action.x == 0) {
                state = State::MoveDown;
            } else if (action.x < 0 && action.y == 0) {
                state = State::MoveLeft;
            } else if (action.x > 0 && action.y == 0) {
                state = State::MoveRight;
            } else {
                state = State::Free;
            }
        }
        if (!transitionHandler.isFinished()) {
            sf::Vector2f velo = ((Entity *)getLastParent())->getAbsoluteVelocity();
            setPosition(transitionHandler.update(delta));
            if (transitionHandler.isFinished()) {
                if (!(*curLane)->receivePlayer(this)) {
                    setDead();
                    if ((*curLane)->getCategory() == ViewCategory::River) {
                        state = State::Drowning;
                    }
                }
                popActionAndUpdateScore();
                if (!isDead()) {
                    state = State::Idle;
                }
            }
        }
    }
}

void PlayerNode::updateCurrent(sf::Time delta) {
    updateMove(delta);

    switch(state) {
        case State::MoveUp:
            moveUp.update(delta);
            moveUp.setRepeating(true);
            break;
        case State::MoveDown:
            moveDown.update(delta);
            moveDown.setRepeating(true);
            break;
        case State::MoveLeft:
            moveLeft.update(delta);
            moveLeft.setRepeating(true);
            break;
        case State::MoveRight:
            moveRight.update(delta);
            moveRight.setRepeating(true);
            break;
    }

    if (state != State::Idle && state != State::Free) {
        sprite.setTextureRect(sf::IntRect(0, 16 * (int)state, 14, 16));
    }
    if (state == State::Dead) {
        sprite.setTextureRect(sf::IntRect(0, 64, 14, 16));
    } else if (state == State::Drowning) {
        sprite.setTextureRect(sf::IntRect(0, 80, 14, 16));
    }

    Entity::updateCurrent(delta);
}

unsigned int PlayerNode::getCategory() const {
    return mCategory;
}

void PlayerNode::setCurrentLane(MapRenderer::LaneList::const_iterator lane) {
    curLane = lane;
}

MapRenderer::LaneList::const_iterator PlayerNode::getCurrentLane() const {
    return curLane;
}

void PlayerNode::moveBack() {
    sf::Vector2i action = getCurrentAction();
    clearActionQueue();
    action *= -1;
    pushAction(action);
    if (action.y < 0) { // go up
        curLane++;
    } else if (action.y > 0) {
        curLane--;
    }
    transitionHandler.setIsReversed(true);
}

void PlayerNode::runAction(const sf::Vector2i &direction) {
    if (direction == sf::Vector2i(0, 0)) {
        return;
    }
    if (direction.y < 0 && direction.x == 0) {
        moveDestination(0, -128);
    } else if (direction.y > 0 && direction.x == 0) {
        moveDestination(0, 128);
    } else if (direction.x < 0 && direction.y == 0) {
        moveDestination(-128, 0);
    } else if (direction.x > 0 && direction.y == 0) {
        moveDestination(128, 0);
    }
}

void PlayerNode::setTransitionLayer(ViewGroup *layer) {
    transitionLayer = layer;
}

void PlayerNode::setLastParent(Entity* parent) {
    lastParent = parent;
}

Entity* PlayerNode::getLastParent() {
    return lastParent;
}

void PlayerNode::pushAction(sf::Vector2i action) {
    actionQueue.push(action);
}

void PlayerNode::popActionAndUpdateScore() {
    sf::Vector2i action = getCurrentAction();
    if (action.y < 0) {
        updateScore(1);
    } else if (action.y > 0) {
        updateScore(-1);
    }
    actionQueue.pop();
}

sf::Vector2i PlayerNode::getCurrentAction() {
    return actionQueue.front();
}

bool PlayerNode::isActionQueueEmpty() const {
    return actionQueue.empty();
}

void PlayerNode::clearActionQueue() {
    while (!actionQueue.empty()) {
        actionQueue.pop();
    }
}

void PlayerNode::setMoveDuration(sf::Time duration) {
    moveDuration = duration;
    moveUp.setDuration(duration);
    moveDown.setDuration(duration);
    moveLeft.setDuration(duration);
    moveRight.setDuration(duration);
}

void PlayerNode::setMoveDuration(float duration) {
    setMoveDuration(sf::seconds(duration));
}

sf::Time PlayerNode::getMoveDuration() const {
    return moveDuration;
}

void PlayerNode::slowDown() {
    setMoveDuration(SLOW_MOVE_DURATION);
}

void PlayerNode::speedUp() {
    setMoveDuration(MOVE_DURATION);
}

bool PlayerNode::isMoving() {
    return getParent() == transitionLayer;
}

void PlayerNode::setDead() {
    __isDead = true;
    state = State::Dead;
}

bool PlayerNode::isDead() const {
    return __isDead;
}

void PlayerNode::savePlayerData(std::ofstream &outf) {
    if (outf.is_open()) {
        PlayerData data;
        data.state = static_cast<int>(state);
        if (isMoving()) {
            data.x = lastParent->getWorldCenter().x;
            data.y = lastParent->getWorldCenter().y;
        } else {
            data.x = getWorldTransform().transformPoint(getOrigin()).x;
            data.y = getWorldTransform().transformPoint(getOrigin()).y;
        }
        data.moveDuration = moveDuration.asSeconds();
        data.currentScore = currentScore;
        data.currentDistance = currentDistance;
        data.isDead = __isDead;

        outf.write(reinterpret_cast<const char *>(&data), sizeof(PlayerData));
    } else {
        std::runtime_error("PLAYERDATA ERR: \"save.data\" cannot be openned.\n");
    }
}

void PlayerNode::loadPlayerData(std::ifstream &inf) {
    if (inf.is_open()) {
        int currentLane = std::distance(lanes.begin(), curLane);
        PlayerData data;
        inf.read(reinterpret_cast<char *>(&data), sizeof(data));

        state = static_cast<State>(data.state);
        setPosition(data.x, data.y);

        moveDuration = sf::seconds(data.moveDuration);
        currentScore = data.currentScore;
        currentDistance = data.currentDistance;
        __isDead = data.isDead;
    } else {
        std::runtime_error("PLAYERDATA ERR: \"save.data\" not found.\n");
    }
}
void PlayerNode::updateScore(int offset) {
    currentDistance += offset;
    currentScore = std::max(currentScore, currentDistance);
}

int PlayerNode::getScore() const {
    return currentScore;
}

void PlayerNode::setPlayerName(std::string name, sf::Font &font) {
    TextView::Ptr playerName = std::make_unique<TextView>(nullptr, name, font, sf::Vector2f(0, 0), 30, sf::Color::White);
    sf::FloatRect playerRect = playerName->getGlobalBounds();
    playerName->setOrigin(playerRect.left + playerRect.width / 2.f, playerRect.top + playerRect.height);
    playerName->setPosition(getBoundingRect().getSize().x / 2.f, 10);
    attachView(std::move(playerName));
}