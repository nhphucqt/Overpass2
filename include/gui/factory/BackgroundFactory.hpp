#ifndef BACKGROUND_FACTORY_HPP
#define BACKGROUND_FACTORY_HPP

#include <SFML/Graphics.hpp>
#include <SpriteView.hpp>
#include <Activity.hpp>

class BackgroundFactory {
public:
    static SpriteView::Ptr create(Activity* context, const sf::Texture& backgroundTexture);
};

#endif