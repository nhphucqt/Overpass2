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
    typedef std::unique_ptr<Activity> ActivityChild;

private:
    std::stack<ActivityChild> activityStack;

public:
    template<typename T>
    void startActivity(Intent::Ptr intent) {
        std::unique_ptr<Activity> activity = std::make_unique<T>();
        activity->setIntent(std::move(intent));
        activity->onCreate();
        attachActivity(std::move(activity));
    }

    void attachActivity(ActivityChild activity);
    void finishActivity(int requestCode, int resultCode, Intent::Ptr data);
    bool isEmpty() const;
    Activity* getCurrentActivity();

private:
    void clearStack();
    void run(sf::RenderWindow& window);
};

#endif