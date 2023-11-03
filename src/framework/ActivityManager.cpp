#include <cassert>
#include <iostream>
#include <ActivityManager.hpp>

void ActivityManager::startActivity(ActivityPtr activity, Intent::Ptr intent)
{
    activity->setIntent(std::move(intent));
    activity->onCreate();
    attachActivity(std::move(activity));
}

void ActivityManager::attachActivity(ActivityPtr activity)
{
    assert(activity != nullptr);
    activity->setActivityManager(this);
    activity->onAttach();
    if (!activityStack.empty())
    {
        getCurrentActivity()->onPause();
    }
    activityStack.push(std::move(activity));
}

void ActivityManager::popStack()
{
    assert(!activityStack.empty());
    getCurrentActivity()->onPause();
    // may do something
    getCurrentActivity()->onDestroy();
    activityStack.pop();
    if (!activityStack.empty())
    {
        getCurrentActivity()->onResume();
        if (requestCode != Intent::NO_REQUEST_CODE)
        {
            getCurrentActivity()->onActivityResult(requestCode, resultCode, std::move(data));
        }
    }
}

void ActivityManager::clearStack()
{
    while (!activityStack.empty())
    {
        getCurrentActivity()->finish();
    }
}

bool ActivityManager::isEmpty() const
{
    return activityStack.empty();
}

Activity *ActivityManager::getCurrentActivity()
{
    return activityStack.top().get();
}

void ActivityManager::run(sf::RenderWindow &mWindow)
{
    if (isEmpty())
    {
        throw std::runtime_error("Activity stack is empty");
    }
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f / 60.f);
    while (mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            getCurrentActivity()->onEvent(event);
            if (isEmpty())
            {
                mWindow.close();
                return;
            }
            if (event.type == sf::Event::Closed)
            {
                std::cout << " >> Window closed" << std::endl;
                clearStack();
                mWindow.close();
                return;
            }
        }
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            getCurrentActivity()->onUpdate();
            assert(!activityStack.empty());
        }
        mWindow.clear(sf::Color::White);
        mWindow.draw(*getCurrentActivity());
        mWindow.display();
    }
}