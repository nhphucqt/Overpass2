#include <Animal.hpp>

TextureID toTextureID(Animal::Type type) {
	switch (type) {
	case Animal::Fox:
		return TextureID::Fox;
 
    // other animals here
	}
	return TextureID::Fox;
}

Animal::Animal(Type mType, const TextureManager& textures): 
type(mType),
animation(textures.get(toTextureID(mType)))
{
    animation.setFrameSize(sf::Vector2i(890/5, 152));
    animation.setNumFrames(5);
    animation.setDuration(sf::seconds(1));
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

Animal::AnimalData Animal::serialize() const {
    AnimalData data;
    data.type = static_cast<int>(type);
	data.posX = getPosition().x;
	data.posY = getPosition().y;
	data.vx = getVelocity().x;
	data.vy = getVelocity().y;
	data.scaleX = getScale().x;
	data.scaleY = getScale().y;

    return data;
}

void Animal::deserialize(Animal::AnimalData& data) {
    type = static_cast<Type>(data.type);
    setPosition(data.posX, data.posY);
	setVelocity(data.vx, data.vy);
	setScale(data.scaleX, data.scaleY);
}
