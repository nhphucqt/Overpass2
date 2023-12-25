#include <PlayerNode.hpp>

PlayerNode::PlayerNode(const TextureManager& textures, std::vector<Lane *>& lanesVct, int currentLane)
: sprite(textures.get(TextureID::CharacterIdle))
, state(State::Idle)
, moveUp(textures.get(TextureID::CharacterUp))
, moveDown(textures.get(TextureID::CharacterDown))
, moveLeft(textures.get(TextureID::CharacterLeft))
, moveRight(textures.get(TextureID::CharacterRight))
, curLane(currentLane)
, lanes(lanesVct)
{
    adaptPosition();
    lastPos = getPosition();
	sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setTextureRect(sf::IntRect(0, 0, 14, 16));

    moveUp.setFrameSize(sf::Vector2i(14, 16));
    moveUp.setNumFrames(4);
    moveUp.setDuration(sf::seconds(0.5));

    moveDown.setFrameSize(sf::Vector2i(14, 16));
    moveDown.setNumFrames(4);
    moveDown.setDuration(sf::seconds(0.5));

    moveLeft.setFrameSize(sf::Vector2i(10, 16));
    moveLeft.setNumFrames(4);
    moveLeft.setDuration(sf::seconds(0.5));

    moveRight.setFrameSize(sf::Vector2i(10, 16));
    moveRight.setNumFrames(4);
    moveRight.setDuration(sf::seconds(0.5));

    sprite.scale(5, 5);
    moveUp.scale(5, 5);
    moveDown.scale(5, 5);
    moveLeft.scale(5, 5);
    moveRight.scale(5, 5);
}

void PlayerNode::move(sf::Vector2f velocity) {
    if (velocity == sf::Vector2f(0, 0))
        state = State::Idle;
    else if (velocity.y < 0 && velocity.x == 0)
        state = State::MoveUp;
    else if (velocity.y > 0 && velocity.x == 0)
        state = State::MoveDown;
    else if (velocity.x < 0 && velocity.y == 0)
        state = State::MoveLeft;
    else if (velocity.x > 0 && velocity.y == 0)
        state = State::MoveRight;
    else
        state = State::Free;
    Entity::setVelocity(velocity);
}

void PlayerNode::move(float vx, float vy) {
    sf::Vector2f velocity(vx, vy);
    move(velocity);
}

PlayerNode::State PlayerNode::getState() {
    return state;
}

void PlayerNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    if (state == MoveUp)
        target.draw(moveUp, states);
    else if (state == MoveDown)
        target.draw(moveDown, states);
    else if (state == MoveLeft)
        target.draw(moveLeft, states);
    else if (state == MoveRight)
        target.draw(moveRight, states);
    else
	    target.draw(sprite, states);
}

void PlayerNode::updateCurrent(sf::Time delta) {
    if (state == MoveUp) {
        moveUp.update(delta);
        moveUp.setRepeating(true);
    }
    else if (state == MoveDown) {
        moveDown.update(delta);
        moveDown.setRepeating(true);
    }
    else if (state == MoveLeft) {
        moveLeft.update(delta);
        moveLeft.setRepeating(true);
    }
    else if (state == MoveRight) {
        moveRight.update(delta);
        moveRight.setRepeating(true);
    }

    if (state != Idle && state != Free) {
        sprite.setTextureRect(sf::IntRect(0, 16 * state, 14, 16));
    }

    sf::Vector2f curPos = getPosition();
    sf::Vector2f posDiff = curPos - lastPos;

    if (posDiff.y <= -128) {
        move(0, 0);
        lastPos = curPos;
        ++curLane;
    }
    else if (posDiff.y >= 128) {
        move(0, 0);
        lastPos = curPos;
        --curLane;
    }
    else if (posDiff.x <= -64 || posDiff.x >= 64) {
        move(0, 0);
        lastPos = curPos;
    }
    else if (posDiff.x <= -64 || posDiff.x >= 64) {
        lastPos = curPos;
    }

    if (state == Idle)
        adaptPosition();

    Entity::updateCurrent(delta);
}

void PlayerNode::adaptPosition() {
    setPosition(getPosition().x, lanes[curLane]->getPosition().y + 24);
}

unsigned int PlayerNode::getCategory() const {
    return Category::Player;
}

sf::FloatRect PlayerNode::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

int PlayerNode::getCurrentLane() {
    return curLane;
}

void PlayerNode::moveBack() {
    setPosition(lastPos);
    move(0, 0);
}
