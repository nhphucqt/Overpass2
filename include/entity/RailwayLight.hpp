#ifndef RAILWAY_LIGHT_HPP
#define RAILWAY_LIGHT_HPP

#include <Entity.hpp>
#include <ResourceID.hpp>
#include <Animation.hpp>

class RailwayLight : public Entity {
public:
    struct RailwayLightData {
        Animation::AnimationData animationData;
        bool isOn;
    };

    typedef std::unique_ptr<RailwayLight> Ptr;

    RailwayLight(TextureHolder& textures);
    void turnOn();
    void turnOff();

    RailwayLightData serialize() const;
    void deserialize(const RailwayLightData& data);

protected:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(sf::Time dt) override;

private:
    bool isOn;
    sf::Texture& onTexture;
    sf::Texture& offTexture;
    Animation animation;

};

#endif