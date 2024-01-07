#include <Entity.hpp>
#include <Vector2dUtils.hpp>
#include <iostream>

Entity::Entity(const sf::Texture &texture) : sprite(texture), mIsReverseSprite(false) {}

void Entity::setSize(sf::Vector2f size)
{
	mSize = size;
}

void Entity::setSize(float x, float y)
{
	mSize.x = x;
	mSize.y = y;
}

sf::Vector2f Entity::getSize() const
{
	return mSize;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

sf::Vector2f Entity::getWorldCenter() const
{
	sf::FloatRect rect = getBoundingRect();
	return sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height / 2);
}

void Entity::updateCurrent(sf::Time dt)
{
	move(mVelocity * dt.asSeconds());
}

void Entity::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	drawBoundingRect(target, states);
}

sf::FloatRect Entity::getLocalBounds() const
{
	return sf::FloatRect(0.f, 0.f, mSize.x, mSize.y);
}

sf::FloatRect Entity::getBoundingRect() const
{
	return getWorldTransform().transformRect(getLocalBounds());
}

void Entity::setHitBox(sf::FloatRect hitBox)
{
	mHitBox = hitBox;
}

sf::FloatRect Entity::getHitBox() const
{
	return getWorldTransform().transformRect(mHitBox);
}

sf::Vector2f Entity::getAbsoluteVelocity() const
{
	sf::Vector2f velocity;
	for (const ViewGroup *node = this; node != nullptr; node = node->getParent())
	{
		if (node->getCategory() != Category::None)
		{
			velocity += ((Entity *)node)->getVelocity();
		}
	}
	return velocity;
}

void Entity::checkSceneCollision(const ViewGroup &sceneGraph, std::set<Pair> &collisionPairs)
{
	if (sceneGraph.getCategory() == Category::None)
	{
		return;
	}
	checkNodeCollision(sceneGraph, collisionPairs);

	for (auto &child : sceneGraph.getViews())
		checkSceneCollision(*child.get(), collisionPairs);
}

void Entity::checkNodeCollision(const ViewGroup &node, std::set<Pair> &collisionPairs)
{
	if (node.getCategory() == Category::None)
	{
		return;
	}
	if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
	{
		ViewGroup *ptr = (ViewGroup *)&node;
		collisionPairs.insert(std::minmax((ViewGroup *)this, ptr));
	}

	for (const ViewGroup::Ptr &child : getViews())
		((Entity *)child.get())->checkNodeCollision(node, collisionPairs);
}

bool collision(const ViewGroup &lhs, const ViewGroup &rhs)
{
	if (lhs.getCategory() == Category::None || rhs.getCategory() == Category::None)
		return false;
	return ((Entity &)lhs).getHitBox().intersects(((Entity &)rhs).getHitBox());
}

float distance(const Entity &lhs, const Entity &rhs)
{
	return Vector2dUtils::length(lhs.getWorldPosition() - rhs.getWorldPosition());
}

float distanceCenter(const Entity &lhs, const Entity &rhs)
{
	sf::FloatRect rectA = lhs.getBoundingRect();
	sf::FloatRect rectB = rhs.getBoundingRect();
	sf::Vector2f centerA(rectA.left + rectA.width / 2, rectA.top + rectA.height / 2);
	sf::Vector2f centerB(rectB.left + rectB.width / 2, rectB.top + rectB.height / 2);
	return Vector2dUtils::distance(centerA, centerB);
}

void Entity::drawBoundingRect(sf::RenderTarget &target, sf::RenderStates) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	sf::FloatRect hitBox = getHitBox();
	sf::RectangleShape hitBoxShape;
	hitBoxShape.setPosition(sf::Vector2f(hitBox.left, hitBox.top));
	hitBoxShape.setSize(sf::Vector2f(hitBox.width, hitBox.height));
	hitBoxShape.setFillColor(sf::Color::Transparent);
	hitBoxShape.setOutlineColor(sf::Color::Blue);
	hitBoxShape.setOutlineThickness(1.f);

	target.draw(shape);
	target.draw(hitBoxShape);
}

void Entity::reverseSprite() {
	sprite.scale(-1, 1);
	mIsReverseSprite = !mIsReverseSprite;
}

bool Entity::isReverseSprite() const {
	return mIsReverseSprite;
}