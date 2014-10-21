#ifndef SIMPLE_LINE_PARSER_VAR_H
#define SIMPLE_LINE_PARSER_VAR_H

#include <string>

#include "convert.h"

namespace slp {

template <typename T>
class Var {
public:
    Var() {}
    Var(const std::string& i_var_name): _name(i_var_name) {}
    const std::string& name() const {
        return _name;
    }
    int load(const char* i_str) {
        return _value.load(i_str);
    }
    const T value() const {
        return _value;
    }
    int value(void* o_ptr) {
        *static_cast<T*>(o_ptr) = this->value();
        return 0;
    }
private:
    T _value;
    std::string _name;
};

#define SPEC_VAR_TYPE(type) \
    template<> \
    int Var<type>::load(const char* i_str); \

SPEC_VAR_TYPE(int);
SPEC_VAR_TYPE(uint32_t);
SPEC_VAR_TYPE(uint64_t);
SPEC_VAR_TYPE(float);
SPEC_VAR_TYPE(double);
SPEC_VAR_TYPE(std::string);

#undef SPEC_VAR_TYPE

} // slp

#endif
