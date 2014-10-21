#ifndef SIMPLE_LINE_PARSER_PARSER_H
#define SIMPLE_LINE_PARSER_PARSER_H

#include "var.h"
#include "list.h"
#include "any.h"
#include "convert.h"

namespace slp {

class Parser {
public:
    Parser() {}
    Parser(const std::string& i_str): _name(i_str) {}

    inline const std::string name() const {
        return _name;
    }

    template<typename T>
    Parser& operator<< (const T& i_t) {
        _parsevec.push_back(Any(i_t));
        const std::string& name = i_t.name();
        if (!name.empty() && 
                _parsemp.find(name) == _parsemp.end()) {
            _parsemp[name] = _parsevec.size() - 1;
        }
        return *this;
    }

    template<typename T>
    Parser& operator, (const T& i_t) {
        return Parser::operator<< (i_t);
    }

    int parse(const char* i_str);
    
    template<typename T>
    int get_value(int idx, T& o_t) {
        return _parsevec[idx].value(o_t);
    }

    template<typename T>
    int get_value(const std::string& key, T& o_t) {
        if (_parsemp.find(key) == _parsemp.end()) {
            return -1;
        }
        return get_value(_parsemp[key], o_t);
    }
private:
    std::string _name;
    std::vector<Any> _parsevec;
    std::map<std::string, int> _parsemp;
};

} // slp

#endif
