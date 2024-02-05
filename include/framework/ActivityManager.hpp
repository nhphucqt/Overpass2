#ifndef ACTIVITY_MANAGER_HPP
#define ACTIVITY_MANAGER_HPP

#include <stack>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Activity.hpp>
#include <Intent.hpp>

class Activity;

class ActivityManager
{
    friend class Application;

public:
    typedef std::unique_ptr<Activity> ActivityPtr;

private:
    std::stack<ActivityPtr> activityStack;
    std::queue<ActivityPtr> finishedActivityQueue;
    sf::RenderWindow mWindow;

public:
    ActivityManager(int windowWidth, int windowHeight, std::string windowTitle);

    void startActivity(ActivityPtr activity, Intent::Ptr intent);
    void attachActivity(ActivityPtr activity);
    void finishActivity(int requestCode, int resultCode, Intent::Ptr data);
    bool isEmpty() const;
    Activity* getCurrentActivity();
    sf::RenderWindow& getWindow();

private:
    void clearStack();
    void run();
};

#endif