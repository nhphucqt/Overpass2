#ifndef MENU_BUTTON_FACTORY_HPP
#define MENU_BUTTON_FACTORY_HPP

#include <Activity.hpp>
#include <SpriteButtonView.hpp>

class MenuButtonFactory {
public:
    static SpriteButtonView::Ptr create(Activity* context, const sf::Texture& texture, const sf::Font& font, const std::string& text, const sf::Vector2f& position, EventListener::EventCallback callback);
};

#endif