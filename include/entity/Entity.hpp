#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <ViewGroup.hpp>

class Entity: public ViewGroup {
public:
	Entity() = default;
	Entity(const sf::Texture &texture);
	virtual void setVelocity(sf::Vector2f velocity);
	virtual void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;
	virtual sf::FloatRect getBoundingRect() const;
	virtual sf::Vector2f center();

protected: 
    sf::Sprite sprite;
	virtual void updateCurrent(sf::Time dt);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Vector2f mVelocity;
};

#endif
