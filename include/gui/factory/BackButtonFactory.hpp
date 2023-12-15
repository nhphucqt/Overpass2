#ifndef BACK_BUTTON_FACTORY_HPP
#define BACK_BUTTON_FACTORY_HPP

#include <SFML/Graphics.hpp>
#include <SpriteButtonView.hpp>
#include <Activity.hpp>

class BackButtonFactory {
public:
    static SpriteButtonView::Ptr create(Activity* context, const sf::Texture& texture, const sf::Font& font);
};

#endif