#include <memory>
#include <string>
#include <iostream>
#include <Application.hpp>

Application::Application(int windowWidth, int windowHeight, std::string windowTitle)
: mWindow(sf::VideoMode(800, 600), "Application") {}

void Application::run() {
    activityManager.run(mWindow);
}