#include "boolean.h"

namespace slp {

int Boolean::load(const char* i_str) {
    std::string s = i_str;

    int ret = -1;
    if (s == "True") {
        _value = true;
        ret = 0;
    } else if (s == "False") {
        _value = false;
        ret = 0;
    }
    return ret;
}

const bool Boolean::value() const {
    return _value;
}

} // slp
