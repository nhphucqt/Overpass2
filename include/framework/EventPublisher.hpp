#ifndef EVENT_PUBLISHER_HPP
#define EVENT_PUBLISHER_HPP

#include <unordered_map>
#include <list>
#include <EventListener.hpp>

class EventListener;

class EventPublisher {
private:
    std::unordered_map<int, std::list<EventListener*>> listeners;

public:
    ~EventPublisher() = default;

    void subscribe(int eventType, EventListener* listener);
    void unsubscribe(int eventType, EventListener* listener);
    void publish(const sf::Event& event);
};

#endif