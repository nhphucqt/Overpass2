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
    EventPublisher* publisher;
    EventCallback onMouseButtonPressed;
    EventCallback onMouseButtonReleased;
    EventCallback onMouseMoved;
    EventCallback onTextEntered;
    bool mIsListening;
    
public:
    EventListener();
    EventListener(EventPublisher* publisher);
    virtual ~EventListener() = default;

    virtual void setOnMouseButtonPressed(EventCallback onMouseButtonPressed);
    virtual void setOnMouseButtonReleased(EventCallback onMouseButtonReleased);
    virtual void setOnMouseMoved(EventCallback onMouseMoved);
    virtual void setOnTextEntered(EventCallback onKeyPressed);

    void unsubscribe();

    void setIsListening(bool isListening);
    bool isListening() const;

    EventPublisher* getPublisher() const;

private:
    void ensurePublisher();
    void eventDispatch(const sf::Event& event);

protected:
    virtual bool isOnMouseButtonPressed(const sf::Event& event) const;
    virtual bool isOnMouseButtonReleased(const sf::Event& event) const;
    virtual bool isOnMouseMoved(const sf::Event& event) const;
    virtual bool isOnTextEntered(const sf::Event& event) const;

    void setPublisher(EventPublisher* publisher);
};

#endif