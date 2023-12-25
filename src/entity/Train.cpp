#include <Train.hpp>

Train::Train(const TextureManager& textures): 
Entity(textures.get(TextureID::Train)) {
	sprite.setOrigin(0, sprite.getGlobalBounds().height);
	scale(0.5, 0.5);
}

unsigned int Train::getCategory() const {
    return Category::Train;
}

sf::FloatRect Train::getBoundingRect() const {
    sf::FloatRect rect = Entity::getBoundingRect();
	rect.top = rect.top + 54;
	rect.height = 128;
	return rect;
}
