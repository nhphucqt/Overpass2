#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include <ViewGroup.hpp>
#include <Intent.hpp>
#include <ActivityManager.hpp>

class ActivityManager;

class Activity: public ViewGroup {
friend class ActivityManager;

public:
    enum ResultCode {
        RESULT_OK,
        RESULT_CANCELED
    };

private:
    ActivityManager* mManager;
    Intent::Ptr mIntent;
    int mResultCode;
    Intent::Ptr mResult;

public:
    Activity();
    ~Activity();

    ActivityManager* getActivityManager();

protected:
    virtual void onEvent(sf::Event& event);
    virtual void onUpdate();
    virtual void onCreate();
    virtual void onAttach();
    virtual void onResume();
    virtual void onPause();
    virtual void onDestroy();
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void onActivityResult(int requestCode, int resultCode, Intent::Ptr data);

    template<typename T>
    void startActivity(Intent::Ptr intent) {
        mManager->startActivity<T>(std::move(intent));
    }

    template<typename T>
    void startActivity() {
        startActivity<T>(Intent::Builder().build());
    }

    Intent* getIntent();

    void setResult(int resultCode, Intent::Ptr data);

    void finish();
private:
    void setActivityManager(ActivityManager* manager);
    void setIntent(Intent::Ptr intent);
};

#endif