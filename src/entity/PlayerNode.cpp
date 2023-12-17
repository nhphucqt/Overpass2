#include <PlayerNode.hpp>


PlayerNode::PlayerNode(const TextureManager& textures)
: sprite(textures.get(TextureID::Player))
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	sprite.scale(0.1, 0.1);
}

void PlayerNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

unsigned int PlayerNode::getCategory() const
{
    return Category::Player;
}

bool PlayerNode::checkCollision(Entity& other) {
   return sprite.getGlobalBounds().intersects(other.getGlobalBounds());
}

sf::FloatRect PlayerNode::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

sf::Vector2f PlayerNode::center() {
    return sf::Vector2f(sprite.getGlobalBounds().getSize().x/2, sprite.getGlobalBounds().getSize().y/2);
}
