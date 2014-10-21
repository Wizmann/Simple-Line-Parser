#ifndef SIMPLE_LINE_PARSER_CONVERT_H
#define SIMPLE_LINE_PARSER_CONVERT_H

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <cmath>

#include <errno.h>
#include <stdint.h>

namespace slp {

int64_t  to_int64 (const char* buffer, int& errcode);
uint64_t to_uint64(const char* buffer, int& errcode);
int32_t  to_int32 (const char* buffer, int& errcode);
uint32_t to_uint32(const char* buffer, int& errcode);
double   to_double(const char* buffer, int& errcode);
float    to_float (const char* buffer, int& errcode);

} // slp

#endif
