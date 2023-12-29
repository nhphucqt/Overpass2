#include <Vehicle.hpp>
#include <AppConfig.hpp>

TextureID toTextureID(Vehicle::Type type) {
	switch (type) {
	case Vehicle::Car:
		return TextureID::Car;

	// other vehicles here
	}
	return TextureID::Car;
}

Vehicle::Vehicle(Type mType, const TextureManager& textures): 
type(mType), 
Entity(textures.get(toTextureID(mType))) {
	sf::Vector2f cellSize = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize);
	setSize(cellSize);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	sprite.setPosition(getBoundingRect().getSize() / 2.f);
	sprite.scale(2, 2);
	setHitBox(sprite.getGlobalBounds());
}

unsigned int Vehicle::getCategory() const {
    return Category::Vehicle;
}
