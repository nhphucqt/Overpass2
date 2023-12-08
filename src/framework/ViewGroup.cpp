#include <cassert>
#include <ViewGroup.hpp>
#include <iostream>
#include <cassert>

void ViewGroup::attachView(Viewable::Ptr view) {
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

void ViewGroup::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawCurrent(target, states);
    for (auto& child : childViews) {
        child->draw(target, states);
    }
}

void ViewGroup::update(sf::Time delta) {
    updateCurrent(delta);
    updateChildren(delta);
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

unsigned int ViewGroup::getCategory() const {
    return Category::None;
}
