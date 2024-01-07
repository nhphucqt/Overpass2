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
}

MyTimer::MyTimerData MyTimer::serialize() {
    MyTimerData data;
    data.invLef = invLef;
    data.invRig = invRig;
    data.time = time.asSeconds();
    data.inv = inv.asSeconds();
    data.timing = timing;
    return data;
}   

void MyTimer::deserialize(MyTimerData data) {
    invLef = data.invLef;
    invRig = data.invRig;
    time = sf::seconds(data.time);
    inv = sf::seconds(data.inv);
    timing = data.timing;
}