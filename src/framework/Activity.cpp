#include <Activity.hpp>
#include <iostream>

Activity::Activity() {
    mManager = nullptr;
    mIntent = nullptr;
    mResultCode = ResultCode::RESULT_CANCELED;
    mResult = nullptr;
}

Activity::~Activity() {
    mManager = nullptr;
}

void Activity::initialize() {
    onLoadResources();
    onCreate();
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

void Activity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    ViewGroup::draw(target, states);
    onDraw(target, states);
}

void Activity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    // Do nothing
}

void Activity::onEvent(const sf::Event& event) {
    // Do nothing
}

void Activity::onEventProcessing() {
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

void Activity::onDestroy() {
    // Do nothing
}

void Activity::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Do nothing
}

void Activity::onActivityResult(int requestCode, ResultCode resultCode, Intent::Ptr data) {
    // Do nothing
}


void Activity::finish() {
    mManager->finishActivity(mIntent->getRequestCode(), (int)mResultCode, std::move(mResult));
}

Intent* Activity::getIntent() const {
    return mIntent.get();
}

void Activity::setResult(ResultCode resultCode, Intent::Ptr data) {
    mResultCode = resultCode;
    mResult = std::move(data);
}

void Activity::setIntent(std::unique_ptr<Intent> intent) {
    mIntent = std::move(intent);
}