#include "convert.h"

namespace slp {

template<typename T>
T strtotype(const char* i_str, char** endptr) {
    return T();
}

template<>
int64_t strtotype(const char* i_str, char** endptr) {
    return strtoll(i_str, endptr, 0);
}

template<>
uint64_t strtotype(const char* i_str, char** endptr) {
    return strtoull(i_str, endptr, 0);
}

template<>
double strtotype(const char* i_str, char** endptr) {
    return strtod(i_str, endptr);
}

template<typename T>
T to_numeric_aux(const char* i_str, int& errcode) {
    errcode = 0;
    if (!i_str) {
        errcode = -1;
        return 0;
    }

    char *end_ptr = NULL;
    errno = 0;
    T val = strtotype<T>(i_str, &end_ptr);

    do {
        if (errno) {
            break;
        }
        if (end_ptr == i_str) {
            break;
        }
        if (!end_ptr) {
            break;
        }
        if (*end_ptr != '\0' && *end_ptr != '\t') {
            break;
        }
        return val;
    } while (0);

    errcode = -1;
    return 0;
}

template<typename DEST_T>
DEST_T to_int(const char* buffer, int& errcode) {
    int64_t val = to_numeric_aux<int64_t>(buffer, errcode);
    if (errcode < 0) {
        return 0;
    }
    if (val < std::numeric_limits<DEST_T>::min() || 
            val > std::numeric_limits<DEST_T>::max()) {
        errcode = -1;
        return 0;
    }
    return static_cast<DEST_T>(val);
}

template<typename DEST_T>
DEST_T to_uint(const char* buffer, int& errcode) {
    if (buffer && *buffer == '-') {
        errcode = -1;
        return -1;
    }
    uint64_t val = to_numeric_aux<uint64_t>(buffer, errcode);
    if (errcode < 0) {
        return 0;
    }
    if (val > std::numeric_limits<DEST_T>::max()) {
        errcode = -1;
        return 0;
    }
    return static_cast<DEST_T>(val);
}

int64_t to_int64(const char* buffer, int& errcode) {
    return to_int<int64_t>(buffer, errcode);
}
uint64_t to_uint64(const char* buffer, int& errcode) {
    return to_uint<uint64_t>(buffer, errcode);
}
int32_t to_int32(const char* buffer, int& errcode) {
    return to_int<int32_t>(buffer, errcode);
}
uint32_t to_uint32(const char* buffer, int& errcode) {
    return to_int<uint32_t>(buffer, errcode);
}
double to_double(const char* buffer, int& errcode) {
    double val = to_numeric_aux<double>(buffer, errcode);
    if (errcode < 0) {
        return 0.0;
    }
    return val;
}
float to_float(const char* buffer, int& errcode) {
    return static_cast<float>(to_double(buffer, errcode));
}

} // slp
