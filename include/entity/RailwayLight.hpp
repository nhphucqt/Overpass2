#ifndef RAILWAY_LIGHT_HPP
#define RAILWAY_LIGHT_HPP

#include <Entity.hpp>
#include <ResourceID.hpp>
#include <Animation.hpp>

class RailwayLight : public Entity {
public:
    typedef std::unique_ptr<RailwayLight> Ptr;

    RailwayLight(TextureManager& textures);
    void turnOn();
    void turnOff();

protected:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(sf::Time dt) override;

private:
    sf::Texture& onTexture;
    sf::Texture& offTexture;
    Animation animation;

};

#endif