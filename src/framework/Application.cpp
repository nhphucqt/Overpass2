#include <memory>
#include <string>
#include <iostream>
#include <Application.hpp>

Application::Application(int windowWidth, int windowHeight, std::string windowTitle)
    : activityManager(windowWidth, windowHeight, windowTitle) {
}

void Application::addLauncher(Activity::Ptr launcher, Intent::Ptr intent)
{
    activityManager.startActivity(std::move(launcher), std::move(intent));
}

void Application::addLauncher(Activity::Ptr launcher)
{
    activityManager.startActivity(std::move(launcher), Intent::Builder().build());
}

void Application::run()
{
    activityManager.run();
}