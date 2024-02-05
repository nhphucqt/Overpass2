#ifndef SIGNUP_ACTIVITY_HPP
#define SIGNUP_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>
#include <EditTextView.hpp>
#include <TextView.hpp>

class SignupActivity : public Activity {
private:
    static const int REQUEST_TITLEBAR_BUTTONS = -1;

    TextureHolder mTextureHolder;
    FontHolder mFontHolder;
    EditTextView* mUsername;
    EditTextView* mPassword;
    EditTextView* mConfirmPassword;
    TextView* mError;

protected:
    virtual void onEvent(const sf::Event& event) override;
    virtual void onCreate() override;
    virtual void onLoadResources() override;

private:
    void createBackground();
    void createTitle();
    void createBackButton();
    void createDialog();
    void checkSignup(const std::string& username, const std::string& password, const std::string& confirmPassword);
};

#endif