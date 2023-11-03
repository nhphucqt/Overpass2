#ifndef EVENT_LISTENER_HPP
#define EVENT_LISTENER_HPP

#include <memory>
#include <functional>
#include <SFML/Window/Event.hpp>
#include <EventPublisher.hpp>

class EventPublisher;

class EventListener {
friend class EventPublisher;

private:
    std::function<void(EventListener* listener, const sf::Event& event)> onMouseButtonPressed;
    std::function<void(EventListener* listener, const sf::Event& event)> onMouseButtonReleased;
    
public:
    virtual ~EventListener() = default;

    void setOnMouseButtonPressed(EventPublisher* publisher, std::function<void(EventListener* listener, const sf::Event& event)> onMouseButtonPressed);
    void setOnMouseButtonReleased(EventPublisher* publisher, std::function<void(EventListener* listener, const sf::Event& event)> onMouseButtonReleased);

private:
    void eventDispatch(const sf::Event& event);

protected:
    virtual bool isOnMouseButtonPressed(const sf::Event& event) const;
    virtual bool isOnMouseButtonReleased(const sf::Event& event) const;
};

#endif