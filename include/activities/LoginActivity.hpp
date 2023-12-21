#ifndef LOGIN_ACTIVITY_HPP
#define LOGIN_ACTIVITY_HPP

#include <Activity.hpp>
#include <ResourceID.hpp>
#include <EditTextView.hpp>
#include <TextView.hpp>

class LoginActivity : public Activity {
private:
    static const int REQUEST_SIGN_UP = 1;
    static const int REQUEST_TITLEBAR_BUTTONS = -1;

    FontManager mFontManager;
    TextureManager mTextureManager;
    EditTextView* mUsername;
    EditTextView* mPassword;
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
    void createBackground();
    void createTitle();
    void createBackButton();
    void createDialog();
    void checkLogin(const std::string& username, const std::string& password);
};

#endif