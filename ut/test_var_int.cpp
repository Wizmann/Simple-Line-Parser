#include <gtest/gtest.h>

#include "var.h"

using slp::Var;

using std::vector;
using std::string;

namespace slp_ut {

TEST(GF_TEST, test_VarInt_normal) {
    int ret = 0;
    Var<int> varint("varint");
    EXPECT_EQ(varint.name(), "varint");

    ret += varint.load("123");
    EXPECT_EQ(varint.value(), 123);

    ret += varint.load("-123");
    EXPECT_EQ(varint.value(), -123);

    ret += varint.load("234\t");
    EXPECT_EQ(varint.value(), 234);

    EXPECT_EQ(ret, 0);
}

TEST(GF_TEST, test_VarInt_out_of_range) {
    int ret = 0;
    Var<int> varint("varint");
    ret = varint.load("0x80000000"); // 1 << 31
    EXPECT_LT(ret, 0);
    EXPECT_EQ(varint.value(), 0);
    ret = varint.load("-0x80000001"); // -( (1 << 31) + 1 )
    EXPECT_LT(ret, 0);
    EXPECT_EQ(varint.value(), 0);
}

TEST(GF_TEST, test_VarInt_not_numeric) {
    int ret = 0;
    Var<int> varint("varint");
    ret = varint.load("");
    EXPECT_LT(ret, 0);
    EXPECT_EQ(varint.value(), 0);

    ret = varint.load(NULL);
    EXPECT_LT(ret, 0);
    EXPECT_EQ(varint.value(), 0);

    ret = varint.load("abc");
    EXPECT_LT(ret, 0);
    EXPECT_EQ(varint.value(), 0);

    ret = varint.load("123abc");
    EXPECT_LT(ret, 0);
    EXPECT_EQ(varint.value(), 0);

    ret = varint.load("123 ");
    EXPECT_LT(ret, 0);
    EXPECT_EQ(varint.value(), 0);
}

TEST(GF_TEST, test_VarUint32_normal) {
    int ret = 0;
    Var<uint32_t> varuint32("varuint32");
    ret = varuint32.load("12345");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(varuint32.value(), 12345U);

    ret = varuint32.load("0xffffffff");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(varuint32.value(), 0xffffffffU);
}

TEST(GF_TEST, test_VarUint32_error) {
    int ret = 0;
    Var<uint32_t> varuint32("varuint32");
    ret = varuint32.load("abc");
    EXPECT_EQ(ret, -1);
    EXPECT_EQ(varuint32.value(), 0U);
    ret = varuint32.load("");
    EXPECT_EQ(ret, -1);
    EXPECT_EQ(varuint32.value(), 0U);
    ret = varuint32.load("-1");
    EXPECT_EQ(ret, -1);
    EXPECT_EQ(varuint32.value(), 0);
    ret = varuint32.load("0x100000000");
    EXPECT_EQ(ret, -1);
    EXPECT_EQ(varuint32.value(), 0U);
}

TEST(GF_TEST, test_VarUint64_normal) {
    int ret = 0;
    Var<uint64_t> varuint64("varuint64");
    ret = varuint64.load("1099511627776");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(varuint64.value(), 1099511627776ULL);

    ret = varuint64.load("0xffffffffffffffff");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(varuint64.value(), 0xffffffffffffffffULL);
}

TEST(GF_TEST, test_VarUint64_error) {
    int ret = 0;
    Var<uint64_t> varuint64("varuint64");
    ret = varuint64.load("abc");
    EXPECT_EQ(ret, -1);
    EXPECT_EQ(varuint64.value(), 0ULL);

    ret = varuint64.load("");
    EXPECT_EQ(ret, -1);
    EXPECT_EQ(varuint64.value(), 0ULL);

    ret = varuint64.load("-2");
    EXPECT_EQ(ret, -1);
    EXPECT_EQ(varuint64.value(), 0ULL);

    ret = varuint64.load("0x10000000000000000");
    EXPECT_EQ(ret, -1);
    EXPECT_EQ(varuint64.value(), 0ULL);
}

} // slp_ut
