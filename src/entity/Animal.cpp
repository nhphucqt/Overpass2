#include <Animal.hpp>

TextureID toTextureID(Animal::Type type) {
	switch (type) {
	case Animal::Fox:
		return TextureID::Fox;
 
    case Animal::Bear:
        return TextureID::Bear;
	}
	return TextureID::Fox;
}

Animal::Animal(Type mType, const TextureManager& textures): 
type(mType),
animation(textures.get(toTextureID(mType)))
{
    if (type == Fox) {
        animation.setFrameSize(sf::Vector2i(890/5, 152));
        animation.setNumFrames(5);
        animation.setDuration(sf::seconds(1));
        animation.scale(0.5, 0.5);
    }
    else if (type == Bear) {
        animation.setFrameSize(sf::Vector2i(156 / 6, 12));
        animation.setNumFrames(6);
        animation.setDuration(sf::seconds(1));
        animation.scale(5, 5);
    }
	// sf::FloatRect bounds = animation.getLocalBounds();
	// animation.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Animal::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(animation, states);
}

sf::FloatRect Animal::getBoundingRect() const {
    return getWorldTransform().transformRect(animation.getGlobalBounds());
}

void Animal::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    animation.update(dt);
    animation.setRepeating(true);
}

unsigned int Animal::getCategory() const {
    return Category::Animal;
}
