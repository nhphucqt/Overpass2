#ifndef SIGNUP_ACTIVITY_HPP
#define SIGNUP_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>
#include <EditTextView.hpp>
#include <TextView.hpp>

class SignupActivity : public Activity {
private:
    FontManager mFontManager;
    EditTextView* mUsername;
    EditTextView* mPassword;
    EditTextView* mConfirmPassword;
    TextView* mError;

protected:
    virtual void onEvent(const sf::Event& event) override;
    virtual void onCreate() override;
    virtual void onLoadResources() override;
    virtual void onAttach() override;
    virtual void onResume() override;
    virtual void onPause() override;
    virtual void onDestroy() override;
    void updateCurrent(sf::Time dt) override;
    virtual void onActivityResult(int requestCode, int resultCode, Intent::Ptr data) override;

private:
    void createTitle();
    void createBackButton();
    void createDialog();
    void checkSignup(const std::string& username, const std::string& password, const std::string& confirmPassword);
};

#endif