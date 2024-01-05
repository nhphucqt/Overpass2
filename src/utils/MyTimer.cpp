#include <MyTimer.hpp>
#include <iostream>

MyTimer::MyTimer(float invLef, float invRig): invLef(invLef), invRig(invRig) {
    time = sf::Time::Zero;
    nextInv();
    stop();
}

void MyTimer::restart() {
    time = sf::Time::Zero;
    nextInv();
    resume();
}

void MyTimer::resume() {
    timing = true;
}

void MyTimer::stop() {
    timing = false;
}

void MyTimer::update(sf::Time dt) {
    if (timing) {
        time += dt;
        // std::cerr << "time: " << time.asSeconds() << std::endl;
    }
}

bool MyTimer::isTimeout() {
    return timing && time.asSeconds() >= inv.asSeconds();
}

bool MyTimer::isTiming() {
    return timing;
}

void MyTimer::nextInv() {
    inv = sf::seconds(MyRandom::random_float(invLef, invRig));
    // std::cerr << "inv: " << inv.asSeconds() << std::endl;
}