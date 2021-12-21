
#ifndef __UTILITIES_
#define __UTILITIES_
#include <string>
#include <cassert>
#include <cctype>
#define pass 0^0

template<typename tp>
size_t write(char *, tp, int);
template<typename tp>
tp transform (const tp &, int, int);
char rev_tp(char);

struct splim
{
    static const int left_align = 1, right_align = -1, non_align = 0;
    //是否有对齐要求:left_align左对齐，right_align右对齐，non_align无对齐要求(default)
    int alignment;
    //对齐宽度。数值应为正整数
    size_t align_width;

    static const int DEC = 10, HEX = 16, OCT = 8;
    //进制系统:DEC = 10(dafault), HEX = 16, OCT = 8
    int numsystem;
    //16进制情况下是否需要大写字母
    bool upperHEX;

    //浮点数保留位数(for double/float) (default:6)
    size_t len_kept;

    static const size_t f = 1, g = 2, e = 3;  
    //浮点数输出格式：f/g/e
    size_t f_type;

    splim ():alignment(non_align),numsystem(DEC),len_kept(6) {}
};

class _Tp {
    size_t __typeTag;
    int __contents;
    splim Task;
public:
    std::string str_contents;
    //重新设置content的内容
    void set_content (const int &);
    void set_content (const std::string &);

    //设置限制的内容
    void set_limits (const splim &);
    
    /*初始化，参数依次为：类型，内容，特殊限制*/
    _Tp (const size_t &Tag, const int &ss, const splim &limits=splim())
    {
        assert(Tag == fmt);
        __typeTag = Tag, __contents = ss;
        Task = limits;
    }
    _Tp (const size_t &Tag, const std::string &ss)
    {
        assert(Tag == str);
        __typeTag = Tag, str_contents = ss;
    }
    enum {str = 0, fmt = 1};

    enum {CHAR = 0, INT = 1, SHORT = 2, LONG = 3, LONGLONG = 4,
        FLOAT = 10, DOUBLE = 11, LONGDOUBLE = 12, STRING = 100};

        
    ~_Tp () {} 
    _Tp () {}
    

    //返回类型：_Tp::str 或 _Tp::fmt
    size_t type() {return __typeTag;}
    
    //@当类型为格式字符串时返回类型。
    int name ();
    
    //@当类型为普通字符串时内容存入char*。结尾补\0
    size_t content (char *);
    
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
            (__contents == _Tp::DOUBLE || __contents == _Tp::FLOAT || __contents == LONGDOUBLE))
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
};
void _Tp::set_content(const int &_x) {
    __contents = _x;
}
void _Tp::set_content(const std::string &_x) {
    str_contents = _x;
}
void _Tp::set_limits(const splim &limits)
{
    Task = limits;
    return;
}

int _Tp::name () {
    if(__typeTag != fmt)
        throw(0);
    return __contents;
}

size_t _Tp::content (char *_re) {
    if(__typeTag != str) 
        throw(0);
    int _len = str_contents.size();
    str_contents.copy(_re, _len);
    _re[_len] = '\0';
    return str_contents.size();
}

size_t _Tp::align_width() {
    if(Task.alignment == splim::non_align) throw(-3);
    return Task.align_width;
}

size_t _Tp::decimals_kept() 
{
    if(type() != _Tp::fmt || !(__contents == DOUBLE || __contents == FLOAT))
        throw(5);
    return Task.len_kept;
}

size_t _Tp::fopt () {
    if(type() != _Tp::fmt) throw(-4);
    if(__contents != FLOAT && __contents != DOUBLE) throw(-5);
    return Task.f_type;
}

const char fmtc[] = "dfgeucs%*";
const size_t fmtl = 9;
//分割format字符串，将其中的字符串/槽位拆分并以_Tp形式储存进arr数组内，返回数组长度
int split (const char *, _Tp *arr);

int split (const char *format, _Tp *arr) 
{

    int len = strlen(format);
    std::string tmp;
    int size = 0;
    for (size_t i = 0; i < len; ++i) {
        if(format[i] == '%')
        {
            if(!tmp.empty()) {arr[size++] = _Tp(_Tp::str, tmp);tmp.clear();}
            //store all related information

            _Tp space = _Tp(_Tp::fmt, _Tp::INT); splim limits = splim();

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
            //[i,end)为占位符部分，需要处理

            int l_counts = 0;
            //[begin, end)
            auto getdigit = [&format](int begin, int end) -> int{
                int res = 0;
                for (int __i = begin; __i < end; ++__i)
                    res = res * 10 + format[__i] - '0';
                return res;
            };
            for(int j = i+1; j<end; ++j) {
                if(format[j] == 'l') l_counts++; //judge whether it's long version
                if(isdigit(format[j])) //caculate its width limits
                {
                    if(format[j-1] == '-')
                        limits.alignment = splim::left_align;
                    else
                        limits.alignment = splim::right_align;
                    int p = j;
                    while(isdigit(format[p])) p++;
                    limits.align_width = getdigit(j, p);
                    j = p;
                }
                if(format[j] == '.') { //caculate its decimal limits(float)
                    int p = j + 1;
                    while(isdigit(format[++p]));
                    limits.len_kept = getdigit(j+1, p);
                    j = p - 1;
                }
                
            }
            switch(format[end]) {
                case 'd':
                    if(l_counts == 0) space.set_content(_Tp::INT);
                    else if (l_counts == 1) space.set_content(_Tp::LONG);
                    else if (l_counts == 2) space.set_content(_Tp::LONGLONG);
                    break;
                case 'u':
                    if(l_counts == 0) space.set_content(-_Tp::INT);
                    else if (l_counts == 1) space.set_content(-_Tp::LONG);
                    else if (l_counts == 2) space.set_content(-_Tp::LONGLONG);
                    break;
                case 'f':
                    limits.f_type = splim::f;
                    if(l_counts == 0) space.set_content(_Tp::FLOAT);
                    else if (l_counts == 1) space.set_content(_Tp::DOUBLE);
                    break;
                case 'g':
                    limits.f_type = splim::g;
                    if(l_counts == 0) space.set_content(_Tp::FLOAT);
                    else if (l_counts == 1) space.set_content(_Tp::DOUBLE);
                    break;
                case 'e':
                    limits.f_type = splim::e;
                    if(l_counts == 0) space.set_content(_Tp::FLOAT);
                    else if (l_counts == 1) space.set_content(_Tp::DOUBLE);
                    break;
                case 's':
                    space.set_content(_Tp::STRING);
                    break;
                case 'c':
                    space.set_content(_Tp::CHAR);
                    break;
            }
            //检测格式字符

            //检测基础字符

            i = end;
            space.set_limits(limits);
            arr[size++] = space;
            tmp.clear();
        }
        else if (format[i] == '\\') {
            if (isdigit(format[i+1])) { //OCT
                int result = 0;
                for (int k = 1; k<=3; ++k){
                    if (isdigit(format[i+k]) && format[i+k] < '8') 
                        result = result*8 + format[i+k] - '0';
                    else break;
                }
                tmp.push_back((char)result);
            }else if (format[i+1] == 'x'){ //HEX
                int result = 0;
                for (int k = 2; k<=3; ++k){
                    if (isdigit(format[i+k]))
                        result = result*16 + format[i+k] - '0';
                    else if(isalpha(format[i+k]) && format[i+k] < 'G')
                        result = result*16 + format[i+k] - 'A';
                    else break;
                }
                tmp.push_back((char)result);
            }else{
                tmp.push_back(rev_tp(format[++i]));
            }
        }
        else tmp.push_back(format[i]);
    }
    if(!tmp.empty()) arr[size++] = _Tp(_Tp::str, tmp);
    return size;
}

//把x以_n进制写进*_tar开头的字符串里
template<typename tp>
size_t write(char *_tar, tp x, int _n) {
    int tmp[100] = {};
    size_t p = 0;
    if(x < 0) _tar[0] = '-', _tar++, x = -x;
    do {
        tmp[p++] = x%_n;
        x /= _n;
    }while(x);
    char *t = _tar;
    for(int i = p-1; i>=0; --i)
    {
        *t = tmp[i]>10?tmp[i]-10+'A':tmp[i]+'0';
        t++;
    }
    _tar[p] = 0;
    return p;
}

//failed
template<typename tp>
tp transform (const tp &x, int src_sys, int tar_sys) {
    char buf[100] = {};
    write(buf, x, src_sys);
}

char rev_tp (char f) {
    switch (f)
    {
        case 'a': return '\a';
        case 'b': return '\b';
        case 'n': return '\n';
        case 't': return '\t';
        case 'f': return '\f';
        case 'r': return '\r';
        case 'v': return '\v';
        case '\\': return '\\';
        case '\'': return '\'';
        case '\"': return '\"';
        case '?': return '?';
        case '0': return 0;
    }
    return f;
}

#endif

