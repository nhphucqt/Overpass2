#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include <Entity.hpp>
#include <Animation.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Animal: public Entity {
public:
    enum Type {Fox};
    Animal(Type mType, const TextureManager& textures);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getBoundingRect() const;
    unsigned int getCategory() const;

private:
    Type type;
    Animation animation;
    void updateCurrent(sf::Time dt);
};

#endif