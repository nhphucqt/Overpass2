#include <AnimalFactory.hpp>
#include <MyRandom.hpp>

const int AnimalFactory::LOG_LEN[NUM_LEN] = {2, 3};

AnimalFactory::AnimalFactory(TextureHolder* textures, bool isReverse, float velocity, float roadLength)
: textures(textures), isReverse(isReverse), velocity(velocity), roadLength(roadLength) {
    nextType();
}

Animal::Ptr AnimalFactory::createAnimal() {
    Animal::Ptr animal(new Animal(getNextType(), *textures));
    if (isReverse) {
        animal->reverseSprite();
        animal->setPosition(roadLength, 0.f);
        animal->setVelocity(-velocity, 0.f);
    } else {
        animal->setPosition(-animal->getSize().x, 0.f);
        animal->setVelocity(velocity, 0.f);
    }
    nextType();
    return std::move(animal);
}

void AnimalFactory::nextType() {
    __nextType = MyRandom::random_range((unsigned int)Animal::Type::Count);
}

Animal::Type AnimalFactory::getNextType() {
    return (Animal::Type)__nextType;
}