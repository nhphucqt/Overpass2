#include <cassert>
#include <ViewGroup.hpp>

void ViewGroup::attachView(ViewChild view) {
    view->setParent(this);
    childViews.push_back(std::move(view));
}

ViewGroup::ViewChild ViewGroup::detachView(const Viewable& view) {
    auto found = std::find_if(childViews.begin(), childViews.end(),
    [&] (ViewChild& p) -> bool { return p.get() == &view; });

    assert(found != childViews.end());

    ViewChild result = std::move(*found);
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