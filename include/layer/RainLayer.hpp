#ifndef RAIN_LAYER_HPP
#define RAIN_LAYER_HPP

#include <SFML/Graphics.hpp>

#include <LayerView.hpp>
#include <MyTimer.hpp>

#include <list>

class RainLayer : public LayerView {
public:
    typedef std::shared_ptr<RainLayer> Ptr;
    
public:
    RainLayer(float worldWidth, float worldHeight);
    RainLayer(sf::Vector2f worldSize);

private:
    static const float DROP_SPEED;
    static const float DROP_LENGTH_LOW;
    static const float DROP_LENGTH_HIG;
    static const float DROP_WIDTH;
    static const float DROP_DELAY_LOW;
    static const float DROP_DELAY_HIG;
    static const float DROP_OFFSET;
    static const float DROP_ANGLE;
    static const int MAX_RAIN_DROPS;

    sf::RectangleShape background;
    sf::Color dropColor;
    std::list<sf::RectangleShape> mDrops;
    MyTimer mTimer;
    sf::Vector2f mWorldSize;

protected:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    virtual void updateCurrent(sf::Time dt) override;

    sf::RectangleShape createDrop();
};

#endif