#include <cassert>
#include <ViewGroup.hpp>
#include <iostream>
#include <cassert>

ViewGroup::ViewGroup(): isReverse(false), mIsUpdate(true), parent(nullptr), mIsVisible(true) {
}

ViewGroup::ViewGroup(EventPublisher* publisher): EventListener(publisher), isReverse(false), mIsUpdate(true), parent(nullptr), mIsVisible(true) {
}

ViewGroup *ViewGroup::getParent() const
{
    return parent;
}

void ViewGroup::setParent(ViewGroup *parent)
{
    this->parent = parent;
}

void ViewGroup::attachView(ViewGroup::Ptr view)
{
    view->setParent(this);
    childViews.push_back(std::move(view));
}

ViewGroup::Ptr ViewGroup::detachView(const ViewGroup &view)
{
    auto found = std::find_if(childViews.begin(), childViews.end(),
                              [&](ViewGroup::Ptr &p) -> bool
                              { return p.get() == &view; });

    assert(found != childViews.end());

    ViewGroup::Ptr result = std::move(*found);
    result->setParent(nullptr);
    childViews.erase(found);
    return std::move(result);
}

void ViewGroup::detachAllViews()
{
    for (auto &view : childViews)
    {
        view->setParent(nullptr);
        view->unsubscribeAll();
    }
    childViews.clear();
}

const std::vector<ViewGroup::Ptr> &ViewGroup::getViews() const
{
    return childViews;
}

void ViewGroup::unsubscribeAll()
{
    unsubscribe();
    for (auto &child : childViews)
    {
        child->unsubscribeAll();
    }
}

void ViewGroup::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!isVisible())
        return;
    states.transform *= getTransform();
    drawCurrent(target, states);
    if (isReverse)
        for (int i = childViews.size() - 1; i >= 0; --i)
            childViews[i]->draw(target, states);
    else
        for (auto &child : childViews)
            child->draw(target, states);
}

void ViewGroup::update(sf::Time delta)
{
    if (isUpdate())
    {
        updateCurrent(delta);
        updateChildren(delta);
    }
}

void ViewGroup::updateCurrent(sf::Time delta)
{
    // do nothing
}

void ViewGroup::updateChildren(sf::Time delta)
{
    // for (ViewGroup::Ptr &child : childViews)
    // {
    //     child->update(delta);
    // }
    for (int i = 0; i < (int)childViews.size(); ++i) {
        childViews[i]->update(delta);
    }
}

void ViewGroup::onCommand(Command &command, sf::Time dt)
{
    // Command current node, if category matches
    if (!command.isUsed && command.category & getCategory())
    {
        command.isUsed = true;
        command.action(*this, dt);
    }

    // Command children
    for (auto &child : childViews)
        child->onCommand(command, dt);
}

void ViewGroup::setReverse(bool reverse)
{
    isReverse = reverse;
}

unsigned int ViewGroup::getCategory() const
{
    return ViewCategory::None;
}

sf::Vector2f ViewGroup::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform ViewGroup::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const ViewGroup *node = this; node != nullptr; node = node->parent)
        transform = node->getTransform() * transform;

    return transform;
}

void ViewGroup::setUpdate(bool isUpdate)
{
    mIsUpdate = isUpdate;
}

bool ViewGroup::isUpdate() {
	return mIsUpdate;
}

void ViewGroup::setVisibility(bool isVisible) {
    mIsVisible = isVisible;
}

bool ViewGroup::isVisible() const {
    return mIsVisible;
}

void ViewGroup::setIsListeningAll(bool isListening) {
    setIsListening(isListening);
    for (auto& child : childViews) {
        child->setIsListeningAll(isListening);
    }
}