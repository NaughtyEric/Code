#define __UTILITIES_
#ifndef _LIBCPP_STRING
#include <string>
#endif

int split (char *format, _Tp *arr) {
    int size = -1, len = strlen(format);
    for (size_t i = 0; i < len; ++i) {
        
    }
}

class _Tp {
    size_t __typeTag;
    std::string __contents;
public:
    static const size_t str = 1;
    static const size_t fmt = 0;

    ~_Tp () {} 
    _Tp () {}

    size_t Type() {return __typeTag;}
    void name (char *_re) {
        if(__typeTag != fmt) throw(0);
        int _len = __contents.size();
        __contents.copy(_re, _len);
        _re[_len] = '\0';
    }
    void str (char *_re) {
        if(__typeTag != str) throw(0);
        int _len = __contents.size();
        __contents.copy(_re, _len);
        _re[_len] = '\0';
    }
};