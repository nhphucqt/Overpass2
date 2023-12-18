#include <Entity.hpp>

Entity::Entity(const sf::Texture &texture): sprite(texture) {}

void Entity::setVelocity(sf::Vector2f velocity) {
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy) {
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const {
	return mVelocity;
}

void Entity::updateCurrent(sf::Time dt) {
	move(mVelocity * dt.asSeconds());
}

void Entity::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

bool Entity::checkCollision(Entity &other) {
    return sprite.getGlobalBounds().intersects(other.getGlobalBounds());
}

sf::FloatRect Entity::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

sf::Vector2f Entity::center() {
    return sf::Vector2f(sprite.getGlobalBounds().getSize().x/2, sprite.getGlobalBounds().getSize().y/2);
}
