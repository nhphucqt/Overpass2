#include <Lane.hpp>

Lane::Lane(const sf::Texture &texture, TextureManager *textures, bool reverse): sprite(texture), laneTextures(textures), isReverse(reverse) {
	sf::IntRect textureRect(0, 0, 1400, 128);
    sprite.setTextureRect(textureRect);
}

void Lane::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}