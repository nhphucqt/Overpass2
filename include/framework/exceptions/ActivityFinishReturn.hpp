#ifndef ACTIVITY_FINISH_RETURN_HPP
#define ACTIVITY_FINISH_RETURN_HPP

#include <exception>

class ActivityFinishReturn: public std::exception {
public:
    virtual ~ActivityFinishReturn() = default;
    virtual const char* what() const noexcept override;
};

#endif
