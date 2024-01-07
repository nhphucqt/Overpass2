#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <ViewGroup.hpp>

class Entity: public ViewGroup {
public:
	Entity();
	Entity(const sf::Texture &texture);
	virtual void setVelocity(sf::Vector2f velocity);
	virtual void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;

	sf::Vector2f getWorldCenter() const;

	sf::FloatRect getLocalBounds() const;
	virtual sf::FloatRect getBoundingRect() const;

	void checkSceneCollision(const ViewGroup& sceneGraph, std::set<Pair>& collisionPairs);
	void checkNodeCollision(const ViewGroup& node, std::set<Pair>& collisionPairs);
	// void removeWrecks();

	void setSize(sf::Vector2f size);
	void setSize(float x, float y);
	sf::Vector2f getSize() const;

	void setHitBox(sf::FloatRect hitBox);
	sf::FloatRect getHitBox() const;

	sf::Vector2f getAbsoluteVelocity() const;

	virtual void reverseSprite();
	bool isReverseSprite() const;

protected: 
    sf::Sprite sprite;
	virtual void updateCurrent(sf::Time dt);
	void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Vector2f mVelocity;
	sf::Vector2f mSize;
	sf::FloatRect mHitBox;
	bool mIsReverseSprite;

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	friend bool collision(const ViewGroup& lhs, const ViewGroup& rhs);
	friend float distance(const Entity& lhs, const Entity& rhs);
	friend float distanceCenter(const Entity& lhs, const Entity& rhs);
};

#endif
