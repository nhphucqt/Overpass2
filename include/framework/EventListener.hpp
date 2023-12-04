#ifndef EVENT_LISTENER_HPP
#define EVENT_LISTENER_HPP

#include <memory>
#include <functional>
#include <SFML/Window/Event.hpp>
#include <EventPublisher.hpp>

class EventPublisher;

class EventListener {
friend class EventPublisher;
public:
    typedef std::function<void(EventListener* listener, const sf::Event& event, std::function<void(EventListener* listener, const sf::Event& event)>)> EventDoubleCallback;
    typedef std::function<void(EventListener* listener, const sf::Event& event)> EventCallback;

private:
    EventCallback onMouseButtonPressed;
    EventCallback onMouseButtonReleased;
    EventCallback onMouseMoved;
    EventCallback onTextEntered;
    
public:
    virtual ~EventListener() = default;

    virtual void setOnMouseButtonPressed(EventPublisher* publisher, EventCallback onMouseButtonPressed);
    virtual void setOnMouseButtonReleased(EventPublisher* publisher, EventCallback onMouseButtonReleased);
    virtual void setOnMouseMoved(EventPublisher* publisher, EventCallback onMouseMoved);
    virtual void setOnTextEntered(EventPublisher* publisher, EventCallback onKeyPressed);

private:
    void eventDispatch(const sf::Event& event);

protected:
    virtual bool isOnMouseButtonPressed(const sf::Event& event) const;
    virtual bool isOnMouseButtonReleased(const sf::Event& event) const;
    virtual bool isOnMouseMoved(const sf::Event& event) const;
    virtual bool isOnTextEntered(const sf::Event& event) const;
};

#endif