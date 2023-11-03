#ifndef ACTIVITY_MANAGER_HPP
#define ACTIVITY_MANAGER_HPP

#include <stack>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Activity.hpp>
#include <Intent.hpp>

class Activity;

class ActivityManager {
friend class Application;

public:
    typedef std::unique_ptr<Activity> ActivityPtr;

private:
    std::stack<ActivityPtr> activityStack;

public:
    void startActivity(ActivityPtr activity, Intent::Ptr intent);
    void attachActivity(ActivityPtr activity);
    void finishActivity(int requestCode, int resultCode, Intent::Ptr data);
    bool isEmpty() const;
    Activity* getCurrentActivity();

private:
    void clearStack();
    void run(sf::RenderWindow& window);
};

#endif