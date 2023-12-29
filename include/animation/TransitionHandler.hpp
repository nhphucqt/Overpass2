#ifndef TRANSITION_HANDLER_HPP
#define TRANSITION_HANDLER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include <memory>
#include <Entity.hpp>

class TransitionHandler {
public:
    class TransitionFunction {
    public:
        virtual float operator()(float t) = 0;
    };

    class TransitionFunctionBenzier: public TransitionFunction {
    public:
        float operator()(float t) override;
    };

    class TransitionFunctionElastic: public TransitionFunction {
    public:
        float operator()(float t) override;
    };

    class TransitionFunctionBounce: public TransitionFunction {
    public:
        float operator()(float t) override;
    };

private:
    Entity* start;
    Entity* end;
    sf::Time duration;
    sf::Time elapsedTime;
    bool isReversed;
    std::unique_ptr<TransitionFunction> transitionFunction;

public:
    void setTransition(Entity* start, Entity* end, sf::Time duration, TransitionFunction* transitionFunction = new TransitionFunctionBenzier());
    sf::Vector2f update(sf::Time delta);
    sf::Vector2f getCurrent() const;
    bool isFinished() const;
    void setIsReversed(bool isReversed);
};

#endif