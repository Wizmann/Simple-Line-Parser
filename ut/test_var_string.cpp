#include <gtest/gtest.h>

#include "var.h"

using slp::Var;

using std::vector;
using std::string;

namespace slp_ut {

TEST(GF_TEST, test_String_normal) {
    int ret = 0;
    Var<string> varstr("varstr");
    EXPECT_EQ(varstr.name(), "varstr");

    ret = varstr.load("�ʻ��ٵ�");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(varstr.value(), "�ʻ��ٵ�");
}

TEST(GF_TEST, test_String_error) {
    int ret = 0;
    Var<string> varstr("varstr");

    ret = varstr.load(NULL);
    EXPECT_LT(ret, 0);
    EXPECT_EQ(varstr.value(), "");
}

} // slp_ut
