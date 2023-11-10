#include <EventPublisher.hpp>
#include <iostream>

void EventPublisher::subscribe(int eventType, EventListener* listener) {
    listeners[eventType].push_back(listener);
}

void EventPublisher::unsubscribe(int eventType, EventListener* listener) {
    listeners[eventType].remove(listener);
}

void EventPublisher::publish(const sf::Event& event) {
    auto listenerIter = listeners.find(event.type);
    if (listenerIter != listeners.end()) {
        for (auto listener: listenerIter->second) {
            listener->eventDispatch(event);
        }
    }
}