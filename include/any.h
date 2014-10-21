#ifndef SIMPLE_LINE_PARSER_ANY_H
#define SIMPLE_LINE_PARSER_ANY_H

#include <cstring>
#include <string>

#include "boost/shared_ptr.hpp"

#include "var.h"
#include "list.h"

namespace slp {

class Any {
private:
    struct Base {
        virtual int load(const char* i_str) = 0;
        virtual std::string name() = 0;
        virtual int value(void* o_ptr) = 0;
        virtual ~Base() {};
    };

    template <typename T>
    struct Data: public Base {
        T m_data;
        Data(const T& i_t): m_data(i_t) {}
        virtual std::string name() {
            return m_data.name();
        }
        virtual int load(const char* i_str) {
            return m_data.load(i_str);
        }
        virtual int value(void* o_ptr) {
            return m_data.value(o_ptr);
        }
    };
public:
    template <typename T>
    Any(const T& i_t): _ptr(new(std::nothrow) Data<T>(i_t)), _err(0) {};

    int load(const char* i_str) {
        if (!_ptr) {
            _err = -1;
            return -1;
        }

        int ret = _ptr->load(i_str);
        _err = ret;
        return ret;
    }

    void reset() {
        _err = 0;
    }

    template <typename T>
    int value(T& o_t) {
        void* o_ptr = static_cast<void*>(&o_t);
        return _ptr->value(o_ptr);
    }

    const std::string name() {
        if (!_ptr) {
            _err = -1;
            return "";
        }
        return _ptr->name();
    }

    bool is_error() {
        return _err < 0;
    }
private:
    boost::shared_ptr<Base> _ptr;
    int _err;
};

} // slp
#endif
