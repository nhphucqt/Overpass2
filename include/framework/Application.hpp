#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>

#include <ActivityManager.hpp>
#include <ActivityID.hpp>

class ActivityManager;

class Application {

private:
    ActivityManager activityManager;

public:
    Application(int windowWidth, int windowHeight, std::string windowTitle); 

    void addLauncher(ActivityID launcher, Intent::Ptr intent);
    void addLauncher(ActivityID launcher);

    void run();
};

#endif