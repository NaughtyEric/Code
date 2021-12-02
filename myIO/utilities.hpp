#define __UTILITIES_
#ifndef _LIBCPP_STRING
#include <string>
#endif
#ifndef _ASSERT_H_
#include <cassert>
#endif

struct splim
{
    static const int left_align = 1, right_align = -1, non_align = 0;
    int alignment;
    int align_length;

    static const unsigned int DEC = 10, BIN = 2, HEX = 16, OCT = 8;
    int numsystem;

    splim ():numsystem(DEC), alignment(non_align) {}
};

class _Tp {
    size_t __typeTag;
    std::string __contents;
    splim Task;
protected:
    //重新设置content的内容
    void set_content (char *);
    void set_limits (const splim &);
public:
    _Tp (const size_t &Tag, const std::string &ss="", const splim &limits=splim())
    {
        assert(Tag <= 1);
        __typeTag = Tag, __contents = ss;
        Task = limits;
    }
    static const size_t str = 0;
    static const size_t fmt = 10;

    ~_Tp () {} 
    _Tp () {}
    /*初始化，参数依次为：类型，内容，特殊限制*/

    //返回类型：_Tp::str 或 _Tp::fmt
    size_t type() {return __typeTag;}
    
    //@当类型为普通字符串时返回内容存入_re
    void content (char *);
    
    //@当类型为格式字符串时返回类型名存入_re
    void name (char *);
    
    //返回对齐情况
    int align_limit()
    {
        return Task.alignment;
    }
    
    //@返回对齐长度（代数值，正数）
    size_t align_length();

    //@返回整数的进制
    int number_system ()
    {
        if(__typeTag != fmt ||
            (__contents == "double" || __contents == "float" || __contents == "long double"))
                throw(233);
        return Task.numsystem;
    }

    friend int split(char*, _Tp[]);
};
void _Tp::set_content(char *_newcontent) {
    __contents = _newcontent;
}

void _Tp::set_limits(const splim &limits)
{
    Task = limits;
    return;
}

void _Tp::content (char *_re) {
    if(__typeTag != str) 
        throw(0);
    int _len = __contents.size();
    __contents.copy(_re, _len);
    _re[_len] = '\0';
}

void _Tp::name (char *_re) {
    if(__typeTag != fmt) 
        throw(0);
    int _len = __contents.size();
    __contents.copy(_re, _len);
    _re[_len] = '\0';
}

size_t _Tp::align_length() {
    if(Task.alignment == splim::non_align) throw(-3);
    return Task.align_length;
}

//分割format字符串，将其中的字符串/槽位拆分并以_Tp形式储存进arr数组内，返回数组长度
int split
    (char *format, _Tp arr[]) 
{
    int size = -1, len = strlen(format);
    std::string tmp;
    int __len = -1;
    for (size_t i = 0; i < len; ++i) {
        if(format[i] == '%') {
            if(!tmp.empty()) {arr[++__len] = _Tp(_Tp::str, tmp);tmp.clear();}
            _Tp space = _Tp(_Tp::fmt);
            //检测格式字符

            //检测基础字符
            i++;
            assert(i < len);
            switch(format[i]) {
                case 'd':
                    space.set_content("int");
                case 'c':
                    space.set_content("char");
            }
        }
        else tmp.push_back(format[i]);
    }
    if(!tmp.empty()) arr[++__len] = _Tp(_Tp::str, tmp);
    return __len;
}
