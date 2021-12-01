#define __UTILITIES_
#ifndef _LIBCPP_STRING
#include <string>
#endif
#ifndef _ASSERT_H_
#include <cassert>
#endif

//分割format字符串，将其中的字符串/槽位拆分并以_Tp形式储存进arr数组内，返回数组长度
int split (char *format, _Tp *arr) {
    int size = -1, len = strlen(format);
    std::string tmp;
    int __len = -1;
    for (size_t i = 0; i < len; ++i) {
        if(format[i] == '%') {
            if(!tmp.empty()) {arr[++__len] = _Tp(_Tp::str, tmp);tmp.clear();}
            _Tp space = _Tp(_Tp::fmt, "");
            //检测格式字符 todo

            //检测基础字符
            i++;
            assert(i < len);
            switch(format[i]) {
                case 'd':
                    space.__set_content("int");
                case 'c':
                    space.Type();
            }
        }
        else tmp.push_back(format[i]);
    }
    if(!tmp.empty()) arr[++__len] = _Tp(_Tp::str, tmp);
    return __len;
}

class _Tp {
    size_t __typeTag;
    std::string __contents;
    size_t __width_lim;
protected:
    void __set_content (std::string ss) {
        __contents = ss;
    }

public:
    static const size_t str = 1;
    static const size_t fmt = 0;

    ~_Tp () {} 
    _Tp () {}
    _Tp (const size_t &Tag, const std::string &ss="", const size_t &width=-1) {
        assert(Tag <= 1);
        __typeTag = Tag, __contents = ss;
        __width_lim = width;
    }

    size_t Type() {return __typeTag;}
    void name (char *_re) {
        if(__typeTag != fmt) throw(0);
        int _len = __contents.size();
        __contents.copy(_re, _len);
        _re[_len] = '\0';
    }
    void content (char *_re) {
        if(__typeTag != str) throw(0);
        int _len = __contents.size();
        __contents.copy(_re, _len);
        _re[_len] = '\0';
    }

    friend int spilt(char *format, _Tp *arr);
};