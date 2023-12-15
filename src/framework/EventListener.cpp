#include <EventListener.hpp>

void EventListener::setOnMouseButtonPressed(EventPublisher* publisher, EventCallback onMouseButtonPressed) {
    this->onMouseButtonPressed = onMouseButtonPressed;
    publisher->unsubscribe(sf::Event::MouseButtonPressed, this);
    publisher->subscribe(sf::Event::MouseButtonPressed, this);
}

void EventListener::setOnMouseButtonReleased(EventPublisher* publisher, EventCallback onMouseButtonReleased) {
    this->onMouseButtonReleased = onMouseButtonReleased;
    publisher->unsubscribe(sf::Event::MouseButtonReleased, this);
    publisher->subscribe(sf::Event::MouseButtonReleased, this);
}

void EventListener::setOnMouseMoved(EventPublisher* publisher, EventCallback onMouseMoved) {
    this->onMouseMoved = onMouseMoved;
    publisher->unsubscribe(sf::Event::MouseMoved, this);
    publisher->subscribe(sf::Event::MouseMoved, this);
}

void EventListener::setOnTextEntered(EventPublisher* publisher, EventCallback onTextEntered) {
    this->onTextEntered = onTextEntered;
    publisher->unsubscribe(sf::Event::TextEntered, this);
    publisher->subscribe(sf::Event::TextEntered, this);
}

void EventListener::eventDispatch(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::MouseButtonPressed:
            if (isOnMouseButtonPressed(event))
                if (onMouseButtonPressed)
                    onMouseButtonPressed(this, event);
            break;
        case sf::Event::MouseButtonReleased:
            if (isOnMouseButtonReleased(event))
                if (onMouseButtonReleased)
                    onMouseButtonReleased(this, event);
            break;
        case sf::Event::MouseMoved:
            if (isOnMouseMoved(event))
                if (onMouseMoved)
                    onMouseMoved(this, event);
            break;
        case sf::Event::TextEntered:
            if (isOnTextEntered(event))
                if (onTextEntered)
                    onTextEntered(this, event);
            break;
    }
}

bool EventListener::isOnMouseButtonPressed(const sf::Event& event) const {
    return true;
}

bool EventListener::isOnMouseButtonReleased(const sf::Event& event) const {
    return true;
}

bool EventListener::isOnMouseMoved(const sf::Event& event) const {
    return true;
}

bool EventListener::isOnTextEntered(const sf::Event& event) const {
    return true;
}