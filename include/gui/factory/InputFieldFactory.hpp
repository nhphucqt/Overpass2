#ifndef INPUT_FIELD_FACTORY_HPP
#define INPUT_FIELD_FACTORY_HPP

#include <Activity.hpp>
#include <EditTextView.hpp>

class InputFieldFactory {
public:
    static EditTextView::Ptr create(Activity* context, const sf::Font& font, const std::string& label, EditTextView::InputType inputType);
};

#endif