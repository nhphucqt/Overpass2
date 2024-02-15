#include <Application.hpp>

#include <string>

Application::Application(int windowWidth, int windowHeight, std::string windowTitle)
: activityManager(windowWidth, windowHeight, windowTitle) {
    // do nothing
}

void Application::addLauncher(ActivityID launcher, Intent::Ptr intent) {
    activityManager.startActivity(launcher, std::move(intent));
}

void Application::addLauncher(ActivityID launcher) {
    activityManager.startActivity(launcher, Intent::Builder().build());
}

void Application::run() {
    activityManager.run();
}