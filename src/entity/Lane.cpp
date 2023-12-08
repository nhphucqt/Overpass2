#include <Lane.hpp>

Lane::Lane(TextureManager* textures): laneTexture(textures) {
	sf::IntRect textureRect(0, 0, 1400, 150);
    sprite.setTexture(laneTexture->get(TextureID::Road));
    sprite.setTextureRect(textureRect);
    buildLane();
}

void Lane::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}

void Lane::loadTextures() {
    laneTexture->load(TextureID::Car, "res/textures/Car.png");
	laneTexture->load(TextureID::TrafficLight, "res/textures/TrafficLight.png");
	laneTexture->load(TextureID::Fox, "res/textures/Fox.png");
}

void Lane::updateCurrent(sf::Time dt) {
    TrafficLight::Color curColor = trafficlight->getCurrentColor();
    if(curColor == TrafficLight::Color::Red)
        for(auto& x : cars)
            x->setVelocity(0, 0);
    else if (curColor == TrafficLight::Color::Green)
        for(auto& x : cars)
			x->setVelocity(300.f, 0.f);
    else
        for(auto& x : cars)
			x->setVelocity(100.f, 0.f);

    Vehicle* lastCar = cars[cars.size() - 1];
    Vehicle* firstCar = cars[0];
    int distance = 1400/cars.size();
    if (lastCar->getPosition().x > 1600)
        cars[cars.size() - 1]->setPosition(firstCar->getPosition().x - 450 - distance, lastCar->getPosition().y);
}

void Lane::buildLane() {
    std::unique_ptr<Vehicle> car(new Vehicle(Vehicle::Car, *laneTexture));
    cars.push_back(car.get());
    car->setPosition(0.f, 75.f);
    car->setVelocity(300.f, 0.f);
    std::unique_ptr<TrafficLight> traffic(new TrafficLight(*laneTexture));
    traffic->setPosition(500.f, 75.f);
    traffic->setVelocity(0.f, 0.f);
    traffic->setScale(0.8, 0.8);
    trafficlight = traffic.get();
    std::unique_ptr<Animal> fox(new Animal(Animal::Fox, *laneTexture));
    fox->setVelocity(100.f, 0.f);
    fox->setPosition(50.f, 75.f);
    fox->setScale(0.7, 0.7);
    this->attachView(std::move(car));
    this->attachView(std::move(fox));
    this->attachView(std::move(traffic));
}