#include <gtest/gtest.h>

#include "var.h"
#include "list.h"
#include "any.h"

using slp::Var;
using slp::List;
using slp::Any;

using std::vector;
using std::string;

namespace slp_ut {

TEST(GF_TEST, test_any_var_normal) {
    vector<Any> vec;
    vec.push_back(Any(Var<int>("varint")));
    vec.push_back(Any(Var<string>("varstring")));
    vec.push_back(Any(Var<float>("varfloat")));

    EXPECT_EQ(vec[0].load("123"), 0);
    EXPECT_EQ(vec[1].load("hello world"), 0);
    EXPECT_EQ(vec[2].load("3.14"), 0);

    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(vec[i].is_error(), false);
    }

    int varint = 0;
    string varstr;
    float varfloat;
    EXPECT_EQ(vec[0].value(varint), 0);
    EXPECT_EQ(varint, 123);

    EXPECT_EQ(vec[1].value(varstr), 0);
    EXPECT_EQ(varstr, "hello world");

    EXPECT_EQ(vec[2].value(varfloat), 0);
    EXPECT_LT(fabs(varfloat - 3.14), 1e-4);

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(vec[i].is_error(), false);
    }
}

TEST(GF_TEST, test_any_var_error) {
    vector<Any> vec;
    vec.push_back(Any(Var<int>("varint")));
    vec.push_back(Any(Var<string>("varstring")));
    vec.push_back(Any(Var<float>("varfloat")));

    EXPECT_EQ(vec[0].load("12.3"), -1);
    EXPECT_EQ(vec[1].load(NULL),   -1);
    EXPECT_EQ(vec[2].load("abc"),  -1);

    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(vec[i].is_error(), true);
        vec[i].reset();
        EXPECT_EQ(vec[i].is_error(), false);
    }
}

TEST(GF_TEST, test_any_list_normal) {
    vector<Any> vec;
    vec.push_back(List<int>("listint"));
    vec.push_back(List<string>("liststr"));
    vec.push_back(List<float>("listfloat"));

    EXPECT_EQ(vec[0].load("3:123,456,789"), 0);
    EXPECT_EQ(vec[1].load("3:do,did,done"), 0);
    EXPECT_EQ(vec[2].load("3:1.11,2.22,3.33"), 0);

    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(vec[i].is_error(), false);
    }

    vector<int> vecint;
    vec[0].value(vecint);
    EXPECT_EQ(vecint[0], 123);
    EXPECT_EQ(vecint[1], 456);
    EXPECT_EQ(vecint[2], 789);

    vector<string> vecstr;
    vec[1].value(vecstr);
    EXPECT_EQ(vecstr[0], "do");
    EXPECT_EQ(vecstr[1], "did");
    EXPECT_EQ(vecstr[2], "done");

    vector<float> vecfloat;
    vec[2].value(vecfloat);
    EXPECT_LT(fabs(vecfloat[0] - 1.11), 1e-3);
    EXPECT_LT(fabs(vecfloat[1] - 2.22), 1e-3);
    EXPECT_LT(fabs(vecfloat[2] - 3.33), 1e-3);
}

TEST(GF_TEST, test_any_mixure_normal) {
    vector<Any> vec;
    vec.push_back(Var<int>("varint"));
    vec.push_back(List<uint32_t>("varuint32"));
    vec.push_back(Var<string>("varstr"));

    EXPECT_EQ(vec[0].load("-1"), 0);
    EXPECT_EQ(vec[1].load("3:0x11,0x22,0x33"), 0);
    EXPECT_EQ(vec[2].load("abc"), 0);

    int varint = 0;
    vector<uint32_t> vecuint32;
    string varstr;

    EXPECT_EQ(vec[0].value(varint), 0);
    EXPECT_EQ(varint, -1);

    EXPECT_EQ(vec[2].value(varstr), 0);
    EXPECT_EQ(varstr, "abc");

    EXPECT_EQ(vec[1].value(vecuint32), 0);
    EXPECT_EQ(vecuint32[0], 0x11U);
    EXPECT_EQ(vecuint32[1], 0x22U);
    EXPECT_EQ(vecuint32[2], 0x33U);
}

} // slp_ut
