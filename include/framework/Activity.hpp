#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include <ViewGroup.hpp>
#include <Intent.hpp>
#include <ActivityManager.hpp>
#include <EventPublisher.hpp>

class ActivityManager;

class Activity: public ViewGroup, 
                public EventPublisher {
friend class ActivityManager;

public: 
    typedef std::unique_ptr<Activity> Ptr;

public:
    enum class ResultCode {
        RESULT_OK,
        RESULT_CANCELED
    };

private:
    ActivityManager* mManager;
    Intent::Ptr mIntent;
    ResultCode mResultCode;
    Intent::Ptr mResult;

public:
    Activity();
    virtual ~Activity() override;

    ActivityManager* getActivityManager();

    void startActivity(Ptr activity, Intent::Ptr intent);
    void startActivity(Ptr activity);

    void finish();
    void setResult(ResultCode resultCode, Intent::Ptr data);
    
protected:
    void initialize();

    virtual void onLoadResources() = 0;
    virtual void onCreate() = 0;
    virtual void onEvent(const sf::Event& event);
    virtual void onEventProcessing();
    virtual void onAttach();
    virtual void onResume();
    virtual void onPause();
    virtual void onDestroy();
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void onActivityResult(int requestCode, ResultCode resultCode, Intent::Ptr data);

    Intent* getIntent() const; 


private:
    void setActivityManager(ActivityManager* manager);
    void setIntent(Intent::Ptr intent);
};

#endif