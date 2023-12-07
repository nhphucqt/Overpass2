#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <ViewGroup.hpp>

class Entity: public ViewGroup {
public:
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;
	void accelerate(sf::Vector2f velocity);
	void accelerate(float vx, float vy);
	virtual unsigned int getCategory() const = 0;

protected: 
    sf::Sprite sprite;
	bool checkCollision(Entity& other);
	sf::FloatRect getGlobalBounds();
	sf::Vector2f center();
	virtual void updateCurrent(sf::Time dt);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f mVelocity;
};

#endif
