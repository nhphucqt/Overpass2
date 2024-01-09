#include <RainLayer.hpp>
#include <MyRandom.hpp>
#include <cmath>

const float RainLayer::DROP_SPEED = 3000.f;
const float RainLayer::DROP_LENGTH_LOW = 5.f;
const float RainLayer::DROP_LENGTH_HIG = 20.f;
const float RainLayer::DROP_WIDTH = 1.f;
const float RainLayer::DROP_DELAY_LOW = 0.005f;
const float RainLayer::DROP_DELAY_HIG = 0.006f;
const float RainLayer::DROP_OFFSET = 200.f;
const float RainLayer::DROP_ANGLE = 10.f;
const int RainLayer::MAX_RAIN_DROPS = 5;

RainLayer::RainLayer(float worldWidth, float worldHeight) : RainLayer(sf::Vector2f(worldWidth, worldHeight)) {
    
}

RainLayer::RainLayer(sf::Vector2f worldSize) : LayerView(), mTimer(DROP_DELAY_LOW, DROP_DELAY_HIG), mWorldSize(worldSize), background(worldSize) {
    mTimer.restart();
    background.setFillColor(sf::Color(0, 0, 0, 128));
    dropColor = sf::Color(255, 255, 255,255);
}

void RainLayer::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
    for (auto &drop : mDrops) {
        target.draw(drop, states);
    }
}

void RainLayer::updateCurrent(sf::Time dt) {
    float angle = DROP_ANGLE * acos(-1) / 180.f;
    float speed = DROP_SPEED * dt.asSeconds();
    for (auto it = mDrops.begin(); it != mDrops.end();) {
        // it->move(0, DROP_SPEED * dt.asSeconds());
        sf::Vector2f offset(- speed * sin(angle), speed * cos(angle));
        it->move(offset);
        if (it->getPosition().y > mWorldSize.y) {
            it = mDrops.erase(it);
        } else {
            ++it;
        }
    }

    mTimer.update(dt);
    if (mTimer.isTimeout()) {
        int numDrops = MyRandom::random_range(1, MAX_RAIN_DROPS);
        while (numDrops--) {
            mDrops.push_back(createDrop());
        }
        mTimer.restart();
    }

}

sf::RectangleShape RainLayer::createDrop() {
    sf::RectangleShape drop(sf::Vector2f(
        DROP_WIDTH,
        MyRandom::random_float(DROP_LENGTH_LOW, DROP_LENGTH_HIG)
    ));
    drop.setPosition(
        MyRandom::random_float(0, mWorldSize.x + mWorldSize.x * tan(DROP_ANGLE * acos(-1) / 180.f)),
        MyRandom::random_float(-DROP_OFFSET, 0)
    );
    drop.setFillColor(dropColor);
    drop.setRotation(DROP_ANGLE);
    return drop;
}