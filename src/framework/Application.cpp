#include <memory>
#include <string>
#include <iostream>
#include <Application.hpp>

Application::Application(int windowWidth, int windowHeight, std::string windowTitle, std::unique_ptr<Activity> launcher)
    : mWindow(sf::VideoMode(800, 600), "Application")
{
    activityManager.attachActivity(std::move(launcher));
}

void Application::run()
{
    activityManager.run(mWindow);
}