#include <Animal.hpp>
#include <AppConfig.hpp>

TextureID toTextureID(Animal::Type type) {
	switch (type) {
    case Animal::Bear:
        return TextureID::Bear;

    case Animal::Boar:
        return TextureID::Boar;

    case Animal::Bunny:
        return TextureID::Bunny;
    
    case Animal::Deer:
        return TextureID::Deer;

    case Animal::Fox:
        return TextureID::Fox;

    case Animal::Wolf:
        return TextureID::Wolf;
	}
	return TextureID::Fox;
}

Animal::Animal(Type mType, const TextureManager& textures)
    :  type(mType)
    , animation(textures.get(toTextureID(mType)))
{
    if (type == Bear) {
        animation.setFrameSize(sf::Vector2i(26, 12));
        animation.setNumFrames(6);
    }
    else if (type == Boar) {
        animation.setFrameSize(sf::Vector2i(16 , 10));
        animation.setNumFrames(4);
    }
    else if (type == Bunny) {
        animation.setFrameSize(sf::Vector2i(11 , 9));
        animation.setNumFrames(4);
    }
    else if (type == Deer) {
        animation.setFrameSize(sf::Vector2i(17 , 18));
        animation.setNumFrames(4);
    }
    else if (type == Fox) {
        animation.setFrameSize(sf::Vector2i(17, 11));
        animation.setNumFrames(4);
    }
    else if (type == Wolf) {
        animation.setFrameSize(sf::Vector2i(19 , 12));
        animation.setNumFrames(6);
    }
    animation.setDuration(sf::seconds(1));
    animation.scale(5, 5);

    sf::Vector2f cellSize = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize);
    setSize(cellSize);
    sf::FloatRect bounds = animation.getLocalBounds();
    animation.setOrigin(bounds.getSize() / 2.f);
    animation.setPosition(cellSize / 2.f);
    setHitBox(animation.getGlobalBounds());
	// sf::FloatRect bounds = animation.getLocalBounds();
	// animation.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Animal::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(animation, states);

    drawBoundingRect(target, states);
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
