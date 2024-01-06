#ifndef MY_TIMER_HPP
#define MY_TIMER_HPP

#include <SFML/System.hpp>
#include <MyRandom.hpp>

class MyTimer {
private:
    float invLef, invRig;
    sf::Time time, inv;
    bool timing;

public:
    MyTimer(float invLef, float invRig);
    void restart();
    void resume();
    void stop();
    void update(sf::Time dt);
    bool isTimeout();
    bool isTiming();

private:
    void nextInv();
};

#endif