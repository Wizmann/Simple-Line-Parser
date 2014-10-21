#include <gtest/gtest.h>

#include "parser.h"

using slp::Parser;
using slp::Var;
using slp::List;

using std::vector;
using std::string;


namespace slp_ut {

TEST(GF_TEST, test_Parser_normal) {
    Parser parser("demo parser");
    parser << Var<int>("winfoid"), Var<float>("winfo_q"), List<string>("winfo_detail"),
              Var<int>("ideaid"), Var<float>("idea_q"), List<string>("idea_detail");
    EXPECT_EQ(parser.parse("123;3.14;3:”Ó÷Ê,∞‘÷˜,±±≥Øœ ;234;0.618;1:SanPang"), 0);
    int varint = 0;
    EXPECT_EQ(parser.get_value(0, varint), 0);
    EXPECT_EQ(varint, 123);
    EXPECT_EQ(parser.get_value(3, varint), 0);
    EXPECT_EQ(varint, 234);

    float varfloat = 0.0;
    EXPECT_EQ(parser.get_value(1, varfloat), 0);
    EXPECT_EQ(parser.get_value("winfo_q", varfloat), 0);
    EXPECT_FLOAT_EQ(varfloat, 3.14);
    EXPECT_EQ(parser.get_value(4, varfloat), 0);
    EXPECT_FLOAT_EQ(varfloat, 0.618);

    vector<string> detvec;
    EXPECT_EQ(parser.get_value(2, detvec), 0);
    EXPECT_EQ(detvec[0], "”Ó÷Ê");
    EXPECT_EQ(detvec[1], "∞‘÷˜");
    EXPECT_EQ(detvec[2], "±±≥Øœ ");
    EXPECT_EQ(parser.get_value(5, detvec), 0);
    EXPECT_EQ(detvec[0], "SanPang");
}

TEST(GF_TEST, test_parser_error) {
    Parser parser1("demo parser");
    parser1 << Var<int>("varint");
    EXPECT_EQ(parser1.parse("abcdefg"), -1);

    Parser parser2("demo parser");
    parser2 << Var<int>("varint") << Var<float>("varfloat") << List<string>("demolist");
    EXPECT_EQ(parser2.parse("1;2;3:a,b"), -1);
}

} // slp_ut
