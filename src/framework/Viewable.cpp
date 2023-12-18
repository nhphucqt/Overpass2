#include <Viewable.hpp>

Viewable::Viewable(): parent(nullptr) {}

Viewable* Viewable::getParent() const {
    return parent;
}

void Viewable::setParent(Viewable* parent) {
    this->parent = parent;
}

void Viewable::update(sf::Time delta) {
    // do nothing
}

sf::Transform Viewable::getAbsoluteTransform() const {
    sf::Transform transform = sf::Transform::Identity;
    for (const Viewable* viewable = this; viewable != nullptr; viewable = viewable->getParent()) {
        transform = viewable->getTransform() * transform;
    }
    return transform;
}

void Viewable::onCommand(const Command &command, sf::Time dt) {
}

sf::Vector2f Viewable::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform Viewable::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const Viewable* node = this; node != nullptr; node = node->parent)
		transform = node->getTransform() * transform;

	return transform;
}

void Viewable::checkSceneCollision(Viewable &sceneGraph, std::set<Pair> &collisionPairs)
{
	checkNodeCollision(sceneGraph, collisionPairs);

	for (Ptr& child : sceneGraph.childViews)
		checkSceneCollision(*child, collisionPairs);
}

void Viewable::checkNodeCollision(Viewable& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
		collisionPairs.insert(std::minmax(this, &node));

	for(Ptr& child : childViews)
		child->checkNodeCollision(node, collisionPairs);
}

sf::FloatRect Viewable::getBoundingRect() const
{
	return sf::FloatRect();
}

void Viewable::removeWrecks()
{
	// Remove all children which request so
	auto wreckfieldBegin = std::remove_if(childViews.begin(), childViews.end(), std::mem_fn(&Viewable::isMarkedForRemoval));
	childViews.erase(wreckfieldBegin, childViews.end());

	// Call function recursively for all remaining children
	std::for_each(childViews.begin(), childViews.end(), std::mem_fn(&Viewable::removeWrecks));
}

bool Viewable::isMarkedForRemoval() const
{
	// By default, remove node if entity is destroyed
	return isDestroyed();
}

bool Viewable::isDestroyed() const
{
	// By default, scene node needn't be removed
	return false;
}

void Viewable::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const {
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

bool collision(const Viewable& lhs, const Viewable& rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

float length(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float distance(const Viewable& lhs, const Viewable& rhs)
{
	return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}