#include <EventListener.hpp>

void EventListener::setOnMouseButtonPressed(EventPublisher* publisher, std::function<void(EventListener* listener, const sf::Event& event)> onMouseButtonPressed) {
    this->onMouseButtonPressed = onMouseButtonPressed;
    publisher->subscribe(sf::Event::MouseButtonPressed, this);
}

void EventListener::setOnMouseButtonReleased(EventPublisher* publisher, std::function<void(EventListener* listener, const sf::Event& event)> onMouseButtonReleased) {
    this->onMouseButtonReleased = onMouseButtonReleased;
    publisher->subscribe(sf::Event::MouseButtonReleased, this);
}

void EventListener::eventDispatch(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::MouseButtonPressed:
            if (isOnMouseButtonPressed(event))
                onMouseButtonPressed(this, event);
            break;
        case sf::Event::MouseButtonReleased:
            if (isOnMouseButtonReleased(event))
                onMouseButtonReleased(this, event);
            break;
    }
}

bool EventListener::isOnMouseButtonPressed(const sf::Event& event) const {
    return true;
}

bool EventListener::isOnMouseButtonReleased(const sf::Event& event) const {
    return true;
}