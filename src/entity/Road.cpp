#include <Road.hpp>

Road::Road(TextureManager *textures, bool isReverse):
Lane(textures->get(TextureID::Road), textures, isReverse) {
    sprite.scale(8.f, 8.f);
	sf::IntRect textureRect(0, 0, 1400, 16);
    sprite.setTextureRect(textureRect);
    buildLane();
}

void Road::updateCurrent(sf::Time dt) {
    if (isReverse) {
        TrafficLight::Color curColor = trafficlight->getCurrentColor();
        if(curColor == TrafficLight::Color::Red)
            for(auto& x : cars)
                x->setVelocity(0, 0);
        else if (curColor == TrafficLight::Color::Green)
            for(auto& x : cars)
                x->setVelocity(-300.f, 0.f);
        else
            for(auto& x : cars)
                x->setVelocity(-100.f, 0.f);

        Vehicle* lastCar = cars[cars.size() - 1];
        Vehicle* firstCar = cars[0];
        int distance = 1400/cars.size();
        if (lastCar->getPosition().x < -200)
            cars[cars.size() - 1]->setPosition(firstCar->getPosition().x + 450 + distance, lastCar->getPosition().y);

        Animal* lastAnimal = animals[animals.size() - 1];
        Animal* firstAnimal = animals[0];
        if (lastAnimal->getPosition().x < -200)
            animals[animals.size() - 1]->setPosition(firstAnimal->getPosition().x + 450 + distance, lastAnimal->getPosition().y);
    }
    else {
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
            cars[cars.size() - 1]->setPosition(firstCar->getPosition().x - 200 - distance, lastCar->getPosition().y);

        Animal* lastAnimal = animals[animals.size() - 1];
        Animal* firstAnimal = animals[0];
        if (lastAnimal->getPosition().x > 1600)
            animals[animals.size() - 1]->setPosition(firstAnimal->getPosition().x - 200 - distance, lastAnimal->getPosition().y);
    }
    
}

void Road::buildLane() {
    if (isReverse) {
        std::unique_ptr<Vehicle> car(new Vehicle(Vehicle::Car, *laneTextures));
        cars.push_back(car.get());
        car->setPosition(1400.f, 64.f);
        car->setVelocity(-300.f, 0.f);
        car->scale(-2.f, 2.f);
        std::unique_ptr<TrafficLight> traffic(new TrafficLight(*laneTextures));
        traffic->setPosition(1000.f, 64.f);
        traffic->setVelocity(0.f, 0.f);
        traffic->scale(0.6, 0.6);
        trafficlight = traffic.get();
        std::unique_ptr<Animal> fox(new Animal(Animal::Fox, *laneTextures));
        animals.push_back(fox.get());
        fox->setVelocity(-100.f, 0.f);
        fox->setPosition(1400.f, 64.f);
        fox->scale(-0.5, 0.5);
        this->attachView(std::move(car));
        this->attachView(std::move(fox));
        this->attachView(std::move(traffic));
    }
    else {
        std::unique_ptr<Vehicle> car(new Vehicle(Vehicle::Car, *laneTextures));
        cars.push_back(car.get());
        car->setPosition(0.f, 64.f);
        car->setVelocity(300.f, 0.f);
        car->scale(2.f, 2.f);
        std::unique_ptr<TrafficLight> traffic(new TrafficLight(*laneTextures));
        traffic->setPosition(400.f, 64.f);
        traffic->setVelocity(0.f, 0.f);
        traffic->scale(0.6, 0.6);
        trafficlight = traffic.get();
        std::unique_ptr<Animal> fox(new Animal(Animal::Fox, *laneTextures));
        animals.push_back(fox.get());
        fox->setVelocity(100.f, 0.f);
        fox->setPosition(0.f, 64.f);
        fox->scale(0.5, 0.5);
        this->attachView(std::move(car));
        this->attachView(std::move(fox));
        this->attachView(std::move(traffic));
    }
    
}