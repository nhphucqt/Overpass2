#include <TransitionHandler.hpp>
#include <cmath>
#include <iostream>

void TransitionHandler::setTransition(Entity* start, Entity* end, sf::Time duration, TransitionFunction* transitionFunction) {
    this->start = start;
    this->end = end;
    this->duration = duration;
    elapsedTime = sf::Time::Zero;
    this->transitionFunction.reset(transitionFunction);
    setIsReversed(false);
}

sf::Vector2f TransitionHandler::update(sf::Time delta) {
    if (!isReversed) {
        elapsedTime += delta;
        if (elapsedTime > duration)
            elapsedTime = duration;
    } else {
        elapsedTime -= delta;
        if (elapsedTime < sf::Time::Zero)
            elapsedTime = sf::Time::Zero;
    }
    return getCurrent();
}

sf::Vector2f TransitionHandler::getCurrent() const {
    float t = elapsedTime.asSeconds() / duration.asSeconds();
    float ratio = transitionFunction->operator()(t);
    sf::Vector2f startPos = start->getWorldCenter();
    sf::Vector2f endPos = end->getWorldCenter();
    return startPos + (endPos - startPos) * ratio;
}

bool TransitionHandler::isFinished() const {
    return isReversed ? elapsedTime == sf::Time::Zero : elapsedTime == duration;
}

void TransitionHandler::setIsReversed(bool isReversed) {
    this->isReversed = isReversed;
}

float TransitionHandler::TransitionFunctionBenzier::operator()(float t) {
    std::pair<double,double> A(0.0, 0.0);
    std::pair<double,double> B(0.42, 0.0);
    std::pair<double,double> C(0.58, 1.0);
    std::pair<double,double> D(1.0, 1.0);
    double tA = -t*t*t + 3*t*t - 3*t + 1;
    double tB = 3*t*t*t - 6*t*t + 3*t;
    double tC = -3*t*t*t + 3*t*t;
    double tD = t*t*t;
    double rY = A.second * tA + B.second * tB + C.second * tC + D.second * tD;
    return rY;
}

float TransitionHandler::TransitionFunctionElastic::operator()(float t) {
    return 1 * (sin(-13.0 * (t + 1.0) * acos(-1)/2) * pow(2.0, -10.0 * t) + 1.0);
}

float TransitionHandler::TransitionFunctionBounce::operator()(float t) {
    const double nl = 7.5625;
    const double dl = 2.75;
    if (t < 1.0 / dl) {
        return nl * t * t;
    } else if (t < 2.0 / dl) {
        t -= 1.5 / dl;
        return nl * t * t + 0.75;
    } else if (t < 2.5 / dl) {
        t -= 2.25 / dl;
        return nl * t * t + 0.9375;
    } else {
        t -= 2.625 / dl;
        return nl * t * t + 0.984375;
    }
}