#ifndef ACTIVITY_GENERATOR_HPP
#define ACTIVITY_GENERATOR_HPP

#include <ActivityID.hpp>
#include <Activity.hpp>

class ActivityGenerator {
private:
    std::map<ActivityID, std::function<Activity::Ptr()>> registeredActivities;

public:
    static ActivityGenerator& getInstance() {
        static ActivityGenerator instance;
        return instance;
    }

    ActivityGenerator(const ActivityGenerator&) = delete;
    ActivityGenerator& operator=(const ActivityGenerator&) = delete;

    Activity::Ptr create(ActivityID id);

    template<typename ActivityType>
    void registerActivity(ActivityID id) {
        registeredActivities[id] = []() -> Activity::Ptr {
            return std::make_unique<ActivityType>();
        };
    }
private:
    ActivityGenerator();

};

#endif