#include <cassert>
#include <iostream>
#include <ActivityManager.hpp>
#include <ActivityFinishReturn.hpp>
#include <AppConfig.hpp>

void ActivityManager::startActivity(ActivityPtr activity, Intent::Ptr intent) {
    activity->setIntent(std::move(intent));
    activity->initialize();
    attachActivity(std::move(activity));
}

void ActivityManager::attachActivity(ActivityPtr activity) {
    assert(activity != nullptr);
    if (!activityStack.empty()) {
        getCurrentActivity()->onPause();
    }
    Activity* activityPtr = activity.get();
    activityStack.push(std::move(activity));
    activityPtr->setActivityManager(this);
    activityPtr->onAttach();
}

void ActivityManager::finishActivity(int requestCode, int resultCode, Intent::Ptr data) {
    assert(!activityStack.empty());
    getCurrentActivity()->onPause();
    // may do something
    getCurrentActivity()->onDestroy();
    activityStack.pop();
    if (!activityStack.empty()) {
        getCurrentActivity()->onResume();
        if (requestCode != Intent::NO_REQUEST_CODE)
        {
            getCurrentActivity()->onActivityResult(requestCode, resultCode, std::move(data));
        }
    }
    throw ActivityFinishReturn();
}

void ActivityManager::clearStack() {
    while (!activityStack.empty()) {
        try {
            getCurrentActivity()->finish();
        } catch (ActivityFinishReturn& e) {
            // do nothing
        }
    }
}

bool ActivityManager::isEmpty() const {
    return activityStack.empty();
}

Activity *ActivityManager::getCurrentActivity() {
    return activityStack.top().get();
}

void ActivityManager::run(sf::RenderWindow &mWindow) {
    if (isEmpty()) {
        throw std::runtime_error("Activity stack is empty");
    }
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f / AppConfig::getInstance().get<int>(ConfigKey::FPS));
    while (mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        sf::Event event;
        while (mWindow.pollEvent(event)) {
            try {
                getCurrentActivity()->publish(event);
                getCurrentActivity()->onEvent(event);
            } catch (ActivityFinishReturn& e) {
                if (isEmpty()) {
                    mWindow.close();
                    return;
                }
            }
            if (event.type == sf::Event::Closed) {
                std::cout << " >> Window closed" << std::endl;
                clearStack();
                mWindow.close();
                return;
            }
        }
        while (timeSinceLastUpdate > timePerFrame)
        {
            getCurrentActivity()->update(timePerFrame);
            assert(!activityStack.empty());
            timeSinceLastUpdate -= timePerFrame;
        }
        mWindow.clear(sf::Color::White);
        mWindow.draw(*getCurrentActivity());
        mWindow.display();
    }
}