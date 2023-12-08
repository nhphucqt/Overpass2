#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <ViewGroup.hpp>

class Entity: public ViewGroup {
public:
	Entity() = default;
	Entity(sf::Texture texture);
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;
	void accelerate(sf::Vector2f velocity);
	void accelerate(float vx, float vy);
	virtual bool checkCollision(Entity& other);
	virtual sf::FloatRect getGlobalBounds();
	virtual sf::Vector2f center();

protected: 
    sf::Sprite sprite;
	virtual void updateCurrent(sf::Time dt);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Vector2f mVelocity;
};

#endif
