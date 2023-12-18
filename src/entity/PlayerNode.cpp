#include <PlayerNode.hpp>

PlayerNode::PlayerNode(const TextureManager& textures, sf::Vector2f initPos)
: sprite(textures.get(TextureID::CharacterIdle))
, state(State::Idle)
, moveUp(textures.get(TextureID::CharacterUp))
, moveDown(textures.get(TextureID::CharacterDown))
, moveLeft(textures.get(TextureID::CharacterLeft))
, moveRight(textures.get(TextureID::CharacterRight))
{
    lastPos = initPos;
    setPosition(lastPos);
	sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setTextureRect(sf::IntRect(0, 0, 48, 48));

    moveUp.setFrameSize(sf::Vector2i(48, 48));
    moveUp.setNumFrames(4);
    moveUp.setDuration(sf::seconds(0.5));

    moveDown.setFrameSize(sf::Vector2i(48, 48));
    moveDown.setNumFrames(4);
    moveDown.setDuration(sf::seconds(0.5));

    moveLeft.setFrameSize(sf::Vector2i(48, 48));
    moveLeft.setNumFrames(4);
    moveLeft.setDuration(sf::seconds(0.5));

    moveRight.setFrameSize(sf::Vector2i(48, 48));
    moveRight.setNumFrames(4);
    moveRight.setDuration(sf::seconds(0.5));

    sprite.scale(5, 5);
    moveUp.scale(5, 5);
    moveDown.scale(5, 5);
    moveLeft.scale(5, 5);
    moveRight.scale(5, 5);
}

void PlayerNode::setVelocity(sf::Vector2f velocity) {
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

void PlayerNode::setVelocity(float vx, float vy) {
    if (vx == 0 && vy == 0)
        state = State::Idle;
    else if (vy < 0 && vx == 0)
        state = State::MoveUp;
    else if (vy > 0 && vx == 0)
        state = State::MoveDown;
    else if (vx < 0 && vy == 0)
        state = State::MoveLeft;
    else if (vx > 0 && vy == 0)
        state = State::MoveRight;
    else
        state = State::Free;
    Entity::setVelocity(vx, vy);
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
        sprite.setTextureRect(sf::IntRect(0, 48 * state, 48, 48));
    }

    sf::Vector2f curPos = getPosition();
    sf::Vector2f posDiff = curPos - lastPos;
    if (posDiff.y <= -64 || posDiff.y >= 64 || posDiff.x <= -64 || posDiff.x >= 64) {
        setVelocity(0, 0);
        lastPos = curPos;
    }
    Entity::updateCurrent(delta);
}

unsigned int PlayerNode::getCategory() const
{
    return Category::Player;
}