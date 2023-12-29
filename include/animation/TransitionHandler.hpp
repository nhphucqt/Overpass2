#ifndef TRANSITION_HANDLER_HPP
#define TRANSITION_HANDLER_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include <memory>

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
    sf::Vector2f start, end;
    sf::Time duration;
    sf::Time elapsedTime;
    bool isReversed;
    std::unique_ptr<TransitionFunction> transitionFunction;

public:
    void setTransition(sf::Vector2f start, sf::Vector2f end, sf::Time duration, TransitionFunction* transitionFunction = new TransitionFunctionBenzier());
    sf::Vector2f update(sf::Time delta);
    sf::Vector2f getCurrent() const;
    bool isFinished() const;
    void move(sf::Vector2f distance);
    void setIsReversed(bool isReversed);
};

#endif