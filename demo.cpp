#include <iostream>
#include <fstream>

#include "var.h"
#include "list.h"
#include "parser.h"
#include "boolean.h"

using slp::Parser;
using slp::Boolean;
using slp::Var;
using slp::List;

int main() {
    const char DATAFILE[] = "data/data.txt";
    Parser shop_info_parser("DemoParser");

    shop_info_parser << Var<uint32_t>("shop_id")
                     << Var<double>("shop_point_x")
                     << Var<double>("shop_point_y")
                     << List<std::string>("lbs_shop_info")
                     << Var<Boolean>("is_active")
                     << List<uint64_t>("query_sign_list");

    std::string buffer;
    std::ifstream ifs(DATAFILE);

    if (!ifs) {
        std::cerr << "File: " << DATAFILE << " open error" << std::endl;
    }

    int ret = 0;
    uint32_t shop_id = 0;
    double shop_point_x = 0;
    double shop_point_y = 0;
    std::vector<std::string> lbs_shop_info;
    std::vector<uint64_t> query_sign_list;
    Boolean is_active;

    while (std::getline(ifs, buffer)) {
        ret = 0;

        ret += shop_info_parser.parse(buffer.c_str());

        ret += shop_info_parser.get_value("shop_id", shop_id);
        ret += shop_info_parser.get_value("shop_point_x", shop_point_x);
        ret += shop_info_parser.get_value("shop_point_y", shop_point_y);
        ret += shop_info_parser.get_value("lbs_shop_info", lbs_shop_info);
        ret += shop_info_parser.get_value("is_active", is_active);
        ret += shop_info_parser.get_value("query_sign_list", query_sign_list);

        if (ret < 0) {
            std::cout << "Error" << std::endl;
            std::cout << "===" << std::endl;
            continue;
        }

        std::cout << "[shop_id]" << std::endl;
        std::cout << shop_id << std::endl;

        std::cout << "[shop_point]" << std::endl;
        std::cout << shop_point_x << ' ' << shop_point_y << std::endl;

        std::cout << "[lbs_shop_info]" << std::endl;
        for (std::vector<std::string>::iterator iter = lbs_shop_info.begin();
                iter != lbs_shop_info.end();
                ++iter) {
            std::cout << *iter << std::endl;
        }

        std::cout << "[is_active]" << std::endl;
        std::cout << (is_active.value()? "True": "False") << std::endl;

        std::cout << "[query_sign_list]" << std::endl;
        for (std::vector<uint64_t>::iterator iter = query_sign_list.begin();
                iter != query_sign_list.end();
                ++iter) {
            printf("%016XLL\n", *iter);
        }

        std::cout << "===" << std::endl;
    }

    return 0;
}
