#ifndef TITLE_BAR_FACTORY_HPP
#define TITLE_BAR_FACTORY_HPP

#include <Activity.hpp>

#include <SpriteView.hpp>
#include <ResourceID.hpp>

class TitlebarFactory {
public:
    enum class TitlebarType {
        NONE,
        SETTINGS,
        PROFILE,
        HELP
    };

    static SpriteView::Ptr create(Activity* context, TextureHolder& mTextureHolder,  const sf::Font& font, const std::string& title, TitlebarType titleType, int requestCode);
};

#endif