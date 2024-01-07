#ifndef ICON_BUTTON_FACTORY_HPP
#define ICON_BUTTON_FACTORY_HPP

#include <Activity.hpp>
#include <SpriteButtonView.hpp>

class IconButtonFactory {
public:
    static SpriteButtonView::Ptr create(Activity* context, const sf::Texture& texture, const sf::Font& font, const sf::Vector2f& position, EventListener::EventCallback callback);
};

#endif