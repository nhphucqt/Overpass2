#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <Activity.hpp>
#include <ActivityManager.hpp>

class Application {

private:
    sf::RenderWindow mWindow;
    ActivityManager activityManager;

public:
    Application(int windowWidth, int windowHeight, std::string windowTitle); 

    template<typename T>
    void addLauncher() {
        activityManager.startActivity<T>(Intent::Builder().build());
    }

    void run();
};

#endif