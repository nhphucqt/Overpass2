#ifndef BACKGROUND_FACTORY_HPP
#define BACKGROUND_FACTORY_HPP

#include <SFML/Graphics.hpp>
#include <SpriteView.hpp>

class BackgroundFactory {
public:
    static SpriteView::Ptr create(const sf::Texture& backgroundTexture);
};

#endif