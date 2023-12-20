#ifndef VIEWABLE_HPP
#define VIEWABLE_HPP

#include <Command.hpp>
#include <CommandQueue.hpp>
#include <memory>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
#include <SFML/Graphics.hpp>

class Viewable: public sf::Drawable, 
                public sf::Transformable {
friend class ViewGroup;

public:
    typedef std::unique_ptr<Viewable> Ptr;
	typedef std::pair<Viewable*, Viewable*> Pair;

protected:
    std::vector<Ptr> childViews;

private:
    Viewable* parent;

public:
    Viewable();
    virtual ~Viewable() = default;
    
    Viewable* getParent() const;
    void setParent(Viewable* parent);

    virtual void update(sf::Time delta);

    sf::Transform getAbsoluteTransform() const;

	sf::Vector2f getWorldPosition() const;
	sf::Transform getWorldTransform() const;

	virtual unsigned int getCategory() const = 0;

	virtual void onCommand(const Command &command, sf::Time dt);
	void checkSceneCollision(Viewable& sceneGraph, std::set<Pair>& collisionPairs);
	void checkNodeCollision(Viewable& node, std::set<Pair>& collisionPairs);
	void removeWrecks();
	virtual sf::FloatRect getBoundingRect() const;
	virtual bool isMarkedForRemoval() const;
	virtual bool isDestroyed() const;
	void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;
};

bool collision(const Viewable& lhs, const Viewable& rhs);
float distance(const Viewable& lhs, const Viewable& rhs);

#endif