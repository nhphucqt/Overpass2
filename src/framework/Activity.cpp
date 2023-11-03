#include <Activity.hpp>
#include <iostream>

Activity::Activity() {
    mManager = nullptr;
    mIntent = nullptr;
    mResultCode = RESULT_CANCELED;
    mResult = nullptr;
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

void Activity::startActivity(Ptr activity, Intent::Ptr intent) {
    mManager->startActivity(std::move(activity), std::move(intent));
}

void Activity::startActivity(Ptr activity) {
    startActivity(std::move(activity), Intent::Builder().build());
}

void Activity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    onDraw(target, states);
}

void Activity::onEvent(const sf::Event& event) {
    // Do nothing
}

void Activity::onUpdate() {
    // Do nothing
}

void Activity::onCreate() {
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

void Activity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data) {
    // Do nothing
}


void Activity::finish() {
    // onPause();
    // onDestroy();
    // mManager->popStack();
    
    mManager->finishActivity(mIntent->getRequestCode(), mResultCode, std::move(mResult));
}

Intent* Activity::getIntent() {
    return mIntent.get();
}

void Activity::setResult(int resultCode, Intent::Ptr data) {
    mResultCode = resultCode;
    mResult = std::move(data);
}

void Activity::setIntent(std::unique_ptr<Intent> intent) {
    mIntent = std::move(intent);
}