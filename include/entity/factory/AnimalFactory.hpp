#ifndef ANIMAL_FACTORY_HPP
#define ANIMAL_FACTORY_HPP

#include <Animal.hpp>
#include <ResourceID.hpp>

class AnimalFactory {
public:
    typedef std::unique_ptr<AnimalFactory> Ptr;

private:
    TextureHolder* textures;
    static const int NUM_LEN = 2;
    static const int LOG_LEN[NUM_LEN];
    bool isReverse;
    float velocity;
    float roadLength;
    int __nextType;

public:
    AnimalFactory(TextureHolder* textures, bool isReverse, float velocity, float riverLength);
    Animal::Ptr createAnimal();

private:
    void nextType();
    Animal::Type getNextType();
};

#endif