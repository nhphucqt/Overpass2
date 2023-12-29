#include <Entity.hpp>
#include <iostream>

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
	// std::cout << "entity is fine1\n";
}

void Entity::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

sf::FloatRect Entity::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

sf::Vector2f Entity::center() {
    return sf::Vector2f(sprite.getGlobalBounds().getSize().x/2, sprite.getGlobalBounds().getSize().y/2);
}
