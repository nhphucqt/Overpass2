#ifndef ACTIVITY_MANAGER_HPP
#define ACTIVITY_MANAGER_HPP

#include <stack>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Activity.hpp>

class Activity;

class ActivityManager
{
    friend class Application;

public:
    typedef std::unique_ptr<Activity> ActivityChild;

private:
    std::stack<ActivityChild>
        activityStack;

public:
    void attachActivity(ActivityChild activity);
    void popStack();
    bool isEmpty() const;
    Activity *getCurrentActivity();

private:
    void clearStack();
    void run(sf::RenderWindow &window);
};

#endif