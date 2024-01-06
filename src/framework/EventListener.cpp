#include <EventListener.hpp>

EventListener::EventListener() : publisher(nullptr), mIsListening(true) {
}

EventListener::EventListener(EventPublisher* publisher) : publisher(publisher), mIsListening(true) {
}

void EventListener::setOnMouseButtonPressed(EventCallback onMouseButtonPressed) {
    ensurePublisher();
    this->onMouseButtonPressed = onMouseButtonPressed;
    publisher->unsubscribe(sf::Event::MouseButtonPressed, this);
    publisher->subscribe(sf::Event::MouseButtonPressed, this);
}

void EventListener::setOnMouseButtonReleased(EventCallback onMouseButtonReleased) {
    ensurePublisher();
    this->onMouseButtonReleased = onMouseButtonReleased;
    publisher->unsubscribe(sf::Event::MouseButtonReleased, this);
    publisher->subscribe(sf::Event::MouseButtonReleased, this);
}

void EventListener::setOnMouseMoved(EventCallback onMouseMoved) {
    ensurePublisher();
    this->onMouseMoved = onMouseMoved;
    publisher->unsubscribe(sf::Event::MouseMoved, this);
    publisher->subscribe(sf::Event::MouseMoved, this);
}

void EventListener::setOnTextEntered(EventCallback onTextEntered) {
    ensurePublisher();
    this->onTextEntered = onTextEntered;
    publisher->unsubscribe(sf::Event::TextEntered, this);
    publisher->subscribe(sf::Event::TextEntered, this);
}

void EventListener::unsubscribe() {
    if (publisher == nullptr)
        return; 
    if (onMouseButtonPressed)
        publisher->unsubscribe(sf::Event::MouseButtonPressed, this);
    if (onMouseButtonReleased)
        publisher->unsubscribe(sf::Event::MouseButtonReleased, this);
    if (onMouseMoved)
        publisher->unsubscribe(sf::Event::MouseMoved, this);
    if (onTextEntered)
        publisher->unsubscribe(sf::Event::TextEntered, this);
}

EventPublisher* EventListener::getPublisher() const {
    return publisher;
}

void EventListener::eventDispatch(const sf::Event& event) {
    if (!isListening())
        return;
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

void EventListener::setPublisher(EventPublisher* publisher) {
    this->publisher = publisher;
}

void EventListener::ensurePublisher() {
    if (publisher == nullptr)
        throw std::runtime_error("Publisher is not set");
}

void EventListener::setIsListening(bool isListening) {
    mIsListening = isListening;
}

bool EventListener::isListening() const {
    return mIsListening;
}