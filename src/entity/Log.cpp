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

Log::Log(Type mType, const TextureManager& textures)
: type(mType)
, Entity(textures.get(toTextureID(mType)))
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

// unsigned int Log::getCategory() const {
//     return Category::Log;
// }