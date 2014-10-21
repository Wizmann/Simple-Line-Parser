#include "parser.h"

namespace slp {

int Parser::parse(const char* i_str) {
    do {
        std::vector<std::string> strvec;
        boost::split(strvec, i_str, boost::is_any_of(";\t"));
        if (strvec.empty()) {
            break;
        }
        if (strvec.size() != _parsevec.size()) {
            break;
        }
        int parser_num = strvec.size();
        int ret = 0;
        for (int i = 0; i < parser_num; i++) {
            ret += _parsevec[i].load(strvec[i].c_str());
        }
        if (ret < 0) {
            break;
        }
        return 0;
    } while (0);

    return -1;
}

} // slp
