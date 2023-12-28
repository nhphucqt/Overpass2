#include <Train.hpp>
#include <AppConfig.hpp>

Train::Train(const TextureManager& textures): 
Entity(textures.get(TextureID::Train)) {
	sf::Vector2f cellSize = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize);
	sf::Vector2f size(cellSize.x * 5, cellSize.y);
	setSize(size);
	sprite.setOrigin(0, sprite.getGlobalBounds().height);
	scale(0.5, 0.5);
	sf::FloatRect rect = sprite.getGlobalBounds();
	rect.top = rect.top + 150;
	rect.height = 128;
	setHitBox(rect);
}

unsigned int Train::getCategory() const {
    return Category::Train;
}
