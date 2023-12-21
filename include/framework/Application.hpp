#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <Activity.hpp>
#include <ActivityManager.hpp>

class ActivityManager;

class Application {

private:
    ActivityManager activityManager;

public:
    Application(int windowWidth, int windowHeight, std::string windowTitle); 

    void addLauncher(Activity::Ptr launcher, Intent::Ptr intent);
    void addLauncher(Activity::Ptr launcher);

    void run();
};

#endif