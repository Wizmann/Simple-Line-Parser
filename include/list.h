#ifndef SIMPLE_LINE_PARSER_LIST_H
#define SIMPLE_LINE_PARSER_LIST_H

#include <vector>
#include <map>

#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"

#include "var.h"
#include "convert.h"

namespace slp {

template <typename T>
class List {
public:
    List() {}
    List(const std::string& i_list_name): _name(i_list_name) {}

    inline const std::string& name() const {
        return _name;
    }

    int load(const char* i_str);
    const std::vector<T> value() const;
    int value(void* o_ptr);
private:
    std::vector<Var<T> > _vec;
    std::string _name;
};

} // slp

#include "list.hpp"

#endif
