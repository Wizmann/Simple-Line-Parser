namespace slp {

template <typename T>
const std::vector<T> List<T>::value() const {
    std::vector<T> ret;
    for (typename std::vector<Var<T> >::const_iterator iter = _vec.begin(); 
            iter != _vec.end(); 
            ++iter) {
        ret.push_back(iter->value());
    }
    return ret;
}

template <typename T>
int List<T>::value(void* o_ptr) {
    std::vector<T>* vec = static_cast<std::vector<T>*>(o_ptr);
    *vec = this->value();
    return 0;
}

template <typename T>
int List<T>::load(const char* i_str) {
    if (i_str == NULL) {
        return -1;
    }
    int ret = 0;
    _vec.clear();

    std::vector<std::string> strvec;
    boost::split(strvec, i_str, boost::is_any_of(":,"));

    if (strvec.empty()) {
        return -1;
    }
    
    size_t len = to_uint32(strvec.begin()->c_str(), ret);
    if (ret < 0) {
        return ret;
    }

    for (std::vector<std::string>::iterator iter = strvec.begin() + 1;
            iter != strvec.end();
            ++iter) {
        Var<T> var_;
        ret = var_.load(iter->c_str());
        if (ret < 0) {
            return ret;
        }
        _vec.push_back(var_);
    }
    if (_vec.size() == len) {
        return 0;
    } else {
        return -1;
    }
}

} // slp
