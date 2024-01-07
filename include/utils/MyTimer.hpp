#ifndef MY_TIMER_HPP
#define MY_TIMER_HPP

#include <SFML/System.hpp>
#include <MyRandom.hpp>

class MyTimer {
public:
    struct MyTimerData {
        float invLef, invRig;
        float time, inv;
        bool timing;
    };

private:
    float invLef, invRig;
    sf::Time time, inv;
    bool timing;

public:
    MyTimer() = default;
    MyTimer(float invLef, float invRig);
    void restart();
    void resume();
    void stop();
    void update(sf::Time dt);
    bool isTimeout();
    bool isTiming();

    MyTimerData serialize();
    void deserialize(MyTimerData data);

private:
    void nextInv();
};

#endif