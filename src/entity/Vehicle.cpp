#include <Vehicle.hpp>

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
Entity(textures.get(toTextureID(type))) {
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}