#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <ActivityManager.hpp>
#include <Activity.hpp>

class Application {

private:
    sf::RenderWindow mWindow;
    ActivityManager activityManager;

public:
    Application(int windowWidth, int windowHeight, std::string windowTitle, std::unique_ptr<Activity> launcher); 
    void run();
};

#endif