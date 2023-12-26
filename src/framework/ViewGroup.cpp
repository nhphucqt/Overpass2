#include <cassert>
#include <ViewGroup.hpp>
#include <iostream>
#include <cassert>

ViewGroup::ViewGroup(): isReverse(false), mIsUpdate(true) {
}

void ViewGroup::attachView(Viewable::Ptr view)
{
    view->setParent(this);
    childViews.push_back(std::move(view));
}

Viewable::Ptr ViewGroup::detachView(const Viewable& view) {
    auto found = std::find_if(childViews.begin(), childViews.end(),
    [&] (Viewable::Ptr& p) -> bool { return p.get() == &view; });

    assert(found != childViews.end());

    Viewable::Ptr result = std::move(*found);
    result->setParent(nullptr);
    childViews.erase(found);
    return result;
}

void ViewGroup::detachAllViews() {
    for (auto& view : childViews) {
        view->setParent(nullptr);
    }
    childViews.clear();
}

const std::vector<Viewable::Ptr>& ViewGroup::getViews() const {
	return childViews;
}

void ViewGroup::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawCurrent(target, states);
    if (isReverse)
        for (int i = childViews.size() - 1; i >= 0; --i)
            childViews[i]->draw(target, states);
    else
        for (auto& child : childViews)
            child->draw(target, states);
    
    drawBoundingRect(target, states);
}

void ViewGroup::update(sf::Time delta) {
	if (isUpdate()) {
		updateCurrent(delta);
		updateChildren(delta);
	}
}

void ViewGroup::updateCurrent(sf::Time delta) {
    // do nothing
}

void ViewGroup::updateChildren(sf::Time delta) {
    for (Viewable::Ptr& child : childViews) {
        child->update(delta);
    }
}

void ViewGroup::onCommand(const Command& command, sf::Time dt) {
	// Command current node, if category matches
	if (command.category & getCategory())
		command.action(*this, dt);

	// Command children
	for(auto& child : childViews)
		child->onCommand(command, dt);
}

void ViewGroup::setReverse(bool reverse) {
    isReverse = reverse;
}

unsigned int ViewGroup::getCategory() const {
    return Category::None;
}

sf::Vector2f ViewGroup::getWorldPosition() const {
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform ViewGroup::getWorldTransform() const {
	sf::Transform transform = sf::Transform::Identity;

	for (const Viewable* node = this; node != nullptr; node = node->parent)
		transform = node->getTransform() * transform;

	return transform;
}

void ViewGroup::checkSceneCollision(const ViewGroup &sceneGraph, std::set<Pair> &collisionPairs) {
	checkNodeCollision(sceneGraph, collisionPairs);

	for (auto& child : sceneGraph.childViews)
		checkSceneCollision(*((ViewGroup*) child.get()), collisionPairs);
}

void ViewGroup::checkNodeCollision(const ViewGroup& node, std::set<Pair>& collisionPairs) {
	if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed()) {
		ViewGroup* ptr = (ViewGroup*) &node;
		collisionPairs.insert(std::minmax(this, ptr));
	}

	for(Viewable::Ptr& child : childViews)
		((ViewGroup*) child.get())->checkNodeCollision(node, collisionPairs);
}

sf::FloatRect ViewGroup::getBoundingRect() const {
	return sf::FloatRect();
}

// void ViewGroup::removeWrecks() {
// 	// Remove all children which request so
// 	auto wreckfieldBegin = std::remove_if(childViews.begin(), childViews.end(), std::mem_fn(&ViewGroup::isMarkedForRemoval));
// 	childViews.erase(wreckfieldBegin, childViews.end());

// 	// Call function recursively for all remaining children
// 	std::for_each(childViews.begin(), childViews.end(), std::mem_fn(&ViewGroup::removeWrecks));
// }

bool ViewGroup::isMarkedForRemoval() const {
	// By default, remove node if entity is destroyed
	return isDestroyed();
}

bool ViewGroup::isDestroyed() const {
	// By default, scene node needn't be removed
	return false;
}

void ViewGroup::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const {
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

bool collision(const ViewGroup& lhs, const ViewGroup& rhs) {
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

float length(sf::Vector2f vector) {
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float distance(const ViewGroup& lhs, const ViewGroup& rhs) {
	return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}

void ViewGroup::setUpdate(bool isUpdate) {
	mIsUpdate = isUpdate;
}

bool ViewGroup::isUpdate() {
	return mIsUpdate;
}