#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include <string>
#include <sstream>

///std::to_string is not recognized by MinGW, so we need to substitute it
namespace helper {
    template<typename T>
    std::string to_string(T value) {
        std::ostringstream os;
        os << value;
        return os.str();
    }
}

#endif // HELPER_H_INCLUDED
