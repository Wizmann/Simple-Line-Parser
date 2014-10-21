# Simple Line Parser

## Introduction

Simple Line Parser is line parser which aim to convert the tab separate line into structured data.

Simple Line Parser support scalar type such as int, uint32_t, uint64_t and double. It also supports string and list. User defined type is also supported if you declare the API ``int load(const char* i_str);``.

The way to use this parser will be easy and well-understood.

## Example

The data may like this.
```
1	0.0	0.0	3:地球,亚洲,中国	True	3:0xaaaaaaaa,0xdeadbeef,0xcccccccccccccccc
```

And we can declare our parser in this way.
```cpp
    Parser shop_info_parser("DemoParser");
    shop_info_parser << Var<uint32_t>("shop_id")
                     << Var<double>("shop_point_x")
                     << Var<double>("shop_point_y")
                     << List<std::string>("lbs_shop_info")
                     << Var<Boolean>("is_active")
                     << List<uint64_t>("query_sign_list");
```

Every field, both var field and list field, has its name. We can easily get the field by its index or name.

## Dependencies

### gtest

Link: [Getting started with Google Test (GTest) on Ubuntu][1]

### boost

sudo apt-get install libboost1.48-all-dev

## Compile

```
cmake CMakeList.txt
make
```

Enjoy~

[1]: http://www.thebigblob.com/getting-started-with-google-test-on-ubuntu/
