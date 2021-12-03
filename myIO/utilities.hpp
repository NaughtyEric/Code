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
    //是否有对齐要求:left_align左对齐，right_align右对齐，non_align无对齐要求(default)
    int alignment;
    //对齐宽度。数值应为正整数
    size_t align_width;

    static const int DEC = 10, BIN = 2, HEX = 16, OCT = 8;
    //进制系统:DEC = 10(dafault), HEX = 16, OCT = 8
    int numsystem;
    //16进制情况下是否需要大写字母
    bool upperHEX;

    //for double/float
    size_t len_kept;

    static const size_t f = 1, g = 2, e = 3;  
    size_t f_type;

    splim ():alignment(non_align),numsystem(DEC),len_kept(6) {}
};

class _Tp {
    size_t __typeTag;
    std::string __contents;
    splim Task;
protected:
    //重新设置content的内容
    void set_content (char *);
    //设置限制的内容
    void set_limits (const splim &);
public:
    _Tp (const size_t &Tag, const std::string &ss="", const splim &limits=splim())
    {
        assert(Tag == str || Tag == fmt);
        __typeTag = Tag, __contents = ss;
        Task = limits;
    }
    static const size_t str = 0;
    static const size_t fmt = 1;

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
    
    //@有对齐时返回对齐长度（代数值，正数）
    size_t align_width();

    //@是整数时返回整数的进制
    int number_system ()
    {
        if(__typeTag != fmt ||
            (__contents == "double" || __contents == "float" || __contents == "long double"))
                throw(233);
        return Task.numsystem;
    }

    //@是16进制时返回大小写
    bool isupper_HEX()
    {
        if(number_system() != splim::HEX) throw(2);
        return Task.upperHEX;
    }

    //@是浮点数时返回保留小数位，默认为6
    size_t decimals_kept();

    //@是浮点数时返回%f %g还是%e
    size_t fopt ();

    friend int split(const char*, _Tp[]);
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

size_t _Tp::align_width() {
    if(Task.alignment == splim::non_align) throw(-3);
    return Task.align_width;
}

size_t _Tp::decimals_kept() 
{
    if(type() != _Tp::fmt || !(__contents == "double" || __contents == "float"))
        throw(5);
    return Task.len_kept;
}

size_t _Tp::fopt () {
    if(type() != _Tp::fmt) throw(-4);
    if(__contents != "float" && __contents != "double") throw(-5);
    return Task.f_type;
}

const char fmtc[] = "dfgeucs%*";
const size_t fmtl = 9;
//分割format字符串，将其中的字符串/槽位拆分并以_Tp形式储存进arr数组内，返回数组长度
int split
    (const char *format, _Tp arr[]) 
{
    int len = strlen(format);
    std::string tmp;
    int size = -1;
    for (size_t i = 0; i < len; ++i) {
        if(format[i] == '%')
        {
            if(!tmp.empty()) {arr[++size] = _Tp(_Tp::str, tmp);tmp.clear();}
            _Tp space = _Tp(_Tp::fmt);
            splim limits = splim();

            size_t end;
            for (end = i+1; end<len; ++end) {
                bool flag = false;
                for (int k = 0; k<=fmtl; ++k)
                    if(fmtc[k] == format[end])
                    {
                        flag = true;
                        break;
                    }
                if (flag) break;
            }
            //i~end为占位符部分，需要处理

            int l_counts = 0;
            for(int j = i+1; j<end; ++j) {
                if(format[j] == 'l') l_counts++;
                if(format[j] == '.') {}
            }
            switch(format[end]) {
                case 'd':
                    if(l_counts == 0) space.set_content("int");
                    else if (l_counts == 1) space.set_content("long");
                    else if (l_counts == 2) space.set_content("long long");
                    break;
                case 'u':
                    if(l_counts == 0) space.set_content("unsigned int");
                    else if (l_counts == 1) space.set_content("unsigned long");
                    else if (l_counts == 2) space.set_content("unsigned long long");
                    break;
                case 'f':
                    
                    if(l_counts == 0) space.set_content("float");
                    else if (l_counts == 1) space.set_content("double");
                    break;
                    
            }
            //检测格式字符

            //检测基础字符

            i = end+1;
        }
        else tmp.push_back(format[i]);
    }
    if(!tmp.empty()) arr[++size] = _Tp(_Tp::str, tmp);
    return size;
}
