#include <ActivityManager.hpp>

#include <cassert>
#include <iostream>

#include <AppConfig.hpp>
#include <ActivityGenerator.hpp>
#include <ActivityProfile.hpp>

ActivityManager::ActivityManager(int windowWidth, int windowHeight, std::string windowTitle)
: mWindow(sf::VideoMode(windowWidth, windowHeight), windowTitle) {
    registerActivities();
}

void ActivityManager::registerActivities() {
    ActivityGenerator& generator = ActivityGenerator::getInstance();
    generator.registerActivity<GameActivity>(ActivityID::Game);
    generator.registerActivity<HelpActivity>(ActivityID::Help);
    generator.registerActivity<LevelsActivity>(ActivityID::Levels);
    generator.registerActivity<LoginActivity>(ActivityID::Login);
    generator.registerActivity<MainMenuActivity>(ActivityID::MainMenu);
    generator.registerActivity<ProfileActivity>(ActivityID::Profile);
    generator.registerActivity<RankingActivity>(ActivityID::Ranking);
    generator.registerActivity<SettingsActivity>(ActivityID::Settings);
    generator.registerActivity<SignupActivity>(ActivityID::Signup);
}

void ActivityManager::startActivity(ActivityPtr activity, Intent::Ptr intent) {
    activity->setIntent(std::move(intent));
    activity->initialize();
    attachActivity(std::move(activity));
}

void ActivityManager::startActivity(ActivityID activityID, Intent::Ptr intent) {
    Activity::Ptr activity = ActivityGenerator::getInstance().create(activityID);
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
    finishedActivityQueue.push(std::move(activityStack.top()));
    activityStack.pop();
    if (!activityStack.empty()) {
        getCurrentActivity()->onResume();
        if (requestCode != Intent::NO_REQUEST_CODE) {
            getCurrentActivity()->onActivityResult(requestCode, (Activity::ResultCode)resultCode, std::move(data));
        }
    }
}

void ActivityManager::clearStack() {
    while (!activityStack.empty()) {
        getCurrentActivity()->finish();
    }
}

bool ActivityManager::isEmpty() const {
    return activityStack.empty();
}

Activity *ActivityManager::getCurrentActivity() {
    return activityStack.top().get();
}

void ActivityManager::run() {
    if (isEmpty()) {
        throw std::runtime_error("Activity stack is empty");
    }

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f / AppConfig::getInstance().get<int>(ConfigKey::FPS));

    while (mWindow.isOpen()) {
        timeSinceLastUpdate += clock.restart();

        while (!finishedActivityQueue.empty()) {
            finishedActivityQueue.pop();
        }

        sf::Event event;
        while (mWindow.pollEvent(event)) {
            getCurrentActivity()->publish(event);
            if (isEmpty()) {
                mWindow.close();
                return;
            }
            getCurrentActivity()->onEvent(event);
            if (isEmpty()) {
                mWindow.close();
                return;
            }
            if (event.type == sf::Event::Closed) {
                std::cout << " >> Window closed" << std::endl;
                clearStack();
                mWindow.close();
                return;
            }
        }
        getCurrentActivity()->onEventProcessing();

        while (timeSinceLastUpdate > timePerFrame) {
            getCurrentActivity()->update(timePerFrame);
            assert(!activityStack.empty());
            timeSinceLastUpdate -= timePerFrame;
        }

        mWindow.clear(sf::Color::White);
        mWindow.draw(*getCurrentActivity());
        mWindow.display();
    }
}

sf::RenderWindow& ActivityManager::getWindow() {
    return mWindow;
}