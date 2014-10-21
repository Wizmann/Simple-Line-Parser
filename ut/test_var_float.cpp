#include <gtest/gtest.h>

#include "var.h"

using slp::Var;

using std::vector;
using std::string;

namespace slp_ut {

TEST(GF_TEST, test_VarFloat_normal) {
    int ret = 0;
    Var<float> varfloat("varfloat");
    EXPECT_EQ(varfloat.name(), "varfloat");
    ret = varfloat.load("123.456");
    EXPECT_FLOAT_EQ(varfloat.value(), 123.456);
    EXPECT_EQ(ret, 0);
}

TEST(GF_TEST, test_VarDouble_normal) {
    int ret = 0;
    Var<double> vardouble("vardouble");
    EXPECT_EQ(vardouble.name(), "vardouble");
    ret = vardouble.load("123.456789");
    EXPECT_FLOAT_EQ(vardouble.value(), 123.456789);
    EXPECT_EQ(ret, 0);
}

TEST(GF_TEST, test_VarDouble_error) {
    int ret = 0;
    Var<double> vardouble("vardouble");
    EXPECT_EQ(vardouble.name(), "vardouble");
    ret = vardouble.load("aa123.456789");
    EXPECT_LT(ret, 0);
    EXPECT_EQ(vardouble.value(), 0);
}

} // slp_ut
