#include <Activity.hpp>

Activity::Activity() {
    mManager = nullptr;
}

Activity::~Activity() {
    mManager = nullptr;
}

ActivityManager* Activity::getActivityManager() {
    return mManager;
}

void Activity::setActivityManager(ActivityManager* manager) {
    mManager = manager;
}

void Activity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    onDraw(target, states);
}

void Activity::onEvent(sf::Event& event) {
    // Do nothing
}

void Activity::onUpdate() {
    // Do nothing
}

void Activity::onAttach() {
    // Do nothing
}

void Activity::onResume() {
    // Do nothing
}

void Activity::onPause() {
    // Do nothing
}

void Activity::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Do nothing
}

void Activity::onDestroy() {
    // Do nothing
}

void Activity::finish() {
    onDestroy();
    mManager->popStack();
}