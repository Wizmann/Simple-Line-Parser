#include <gtest/gtest.h>

#include "list.h"

using slp::List;

using std::vector;
using std::string;

namespace slp_ut {

TEST(GF_TEST, test_int_line_normal) {
    string input = "3:1,2,3";
    List<int> intlist("intlist");

    EXPECT_EQ(intlist.name(), "intlist");
    EXPECT_EQ(intlist.load(input.c_str()), 0);

    vector<int> vec = intlist.value();
    for (int i = 0; i < (int)vec.size(); i++) {
        EXPECT_EQ(vec[i], i + 1);
    }
}

TEST(GF_TEST, test_string_line_normal) {
    string input = "5:eins,zwei,drei,vier,f¨¹nf";
    List<string> strlist("strlist");

    EXPECT_EQ(strlist.load(input.c_str()), 0);
    vector<string> vec = strlist.value();
    EXPECT_EQ(vec[0], "eins");
    EXPECT_EQ(vec[1], "zwei");
    EXPECT_EQ(vec[2], "drei");
    EXPECT_EQ(vec[3], "vier");
    EXPECT_EQ(vec[4], "f¨¹nf");
}

TEST(GF_TEST, test_int_line_error) {
    List<int> intlist("intlist");

    EXPECT_EQ(intlist.load(NULL), -1);
    EXPECT_EQ(intlist.load("123345"), -1);
    EXPECT_EQ(intlist.load("2:"), -1);
    EXPECT_EQ(intlist.load("-1:"), -1);
    EXPECT_EQ(intlist.load("1:2,3"), -1);
    EXPECT_EQ(intlist.load("1:0x80000000"), -1);
}

} // slp_ut
