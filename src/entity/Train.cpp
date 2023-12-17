#include <Train.hpp>

Train::Train(const TextureManager& textures): 
Entity(textures.get(TextureID::Train)) {
	sprite.setOrigin(0, sprite.getGlobalBounds().height);
}

unsigned int Train::getCategory() const {
    return Category::Train;
}
