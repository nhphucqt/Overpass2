#include <Log.hpp>

TextureID toTextureID(Log::Type type) {
	switch (type) {
	case Log::Wood:
		return TextureID::Wood;

	case Log::Crocodile:
		return TextureID::Crocodile;
	}
	return TextureID::Wood;
}

Log::Log(Type mType, const TextureManager& textures):
type(mType),
Entity(textures.get(toTextureID(mType)))
{
	sprite.scale(8, 8);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

unsigned int Log::getCategory() const {
	switch (type) {
	case Log::Wood:
		return Category::Wood;
	case Log::Crocodile:
		return Category::Crocodile;
	default:
		return Category::Wood;
	}
}