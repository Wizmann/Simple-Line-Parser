#include "var.h"

namespace slp {

#define TO_NUMERIC(i_str, func) \
    do { \
        int err = 0; \
        _value = func(i_str, err); \
        if (err < 0) { \
            _value = 0; \
            return -1; \
        } \
        return 0; \
    } while (0)


template <>
int Var<int>::load(const char* i_str) {
    TO_NUMERIC(i_str, to_int32);
}

template <>
int Var<uint32_t>::load(const char *i_str) {
    TO_NUMERIC(i_str, to_uint32);
}

template<>
int Var<uint64_t>::load(const char *i_str) {
    TO_NUMERIC(i_str, to_uint64);
}

template<>
int Var<float>::load(const char* i_str) {
    TO_NUMERIC(i_str, to_float);
}

template<>
int Var<double>::load(const char* i_str) {
    TO_NUMERIC(i_str, to_double);
}

template<>
int Var<std::string>::load(const char* i_str) {
    if (!i_str) {
        _value = "";
        return -1;
    }
    _value = std::string(i_str);
    return 0;
}

} // slp
