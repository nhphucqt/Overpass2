#ifndef SETTING_TOGGLE_FACTORY_HPP
#define SETTING_TOGGLE_FACTORY_HPP

#include <Activity.hpp>
#include <ToggleButtonView.hpp>

class SettingToggleFactory {
public:
    static ToggleButtonView::Ptr create(Activity* activity, sf::Texture& texture, sf::Font& font, const std::string& label, bool isOn);
};

#endif