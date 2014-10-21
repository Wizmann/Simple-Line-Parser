#ifndef SIMPLE_LINE_PARSER_BOOLEAN_H
#define SIMPLE_LINE_PARSER_BOOLEAN_H

#include <string>

namespace slp {

class Boolean {
public:
    int load(const char* i_str);
    const bool value() const;
private:
    bool _value;
};

} // slp

#endif 
