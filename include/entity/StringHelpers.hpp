#ifndef STRINGHELPERS_HPP
#define STRINGHELPERS_HPP

#include <sstream>

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

#endif
