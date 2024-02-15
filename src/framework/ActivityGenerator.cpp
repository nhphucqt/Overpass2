#include <ActivityGenerator.hpp>

ActivityGenerator::ActivityGenerator() {
    // do nothing
}

Activity::Ptr ActivityGenerator::create(ActivityID id) {
    return registeredActivities[id]();
}