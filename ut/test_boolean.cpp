#include <gtest/gtest.h>

#include "boolean.h"

using slp::Boolean;

namespace slp_ut {

TEST(GF_TEST, test_boolean_normal) {
    Boolean boolvar;

    EXPECT_EQ(boolvar.load("True"), 0);
    EXPECT_TRUE(boolvar.value());

    EXPECT_EQ(boolvar.load("False"), 0);
    EXPECT_FALSE(boolvar.value());
}

TEST(GF_TEST, test_boolean_error) {
    Boolean boolvar;
    EXPECT_EQ(boolvar.load("China"), -1);
}

} // slp_ut
