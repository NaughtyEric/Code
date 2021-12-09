# MYIO

## utilities.h

### splim

#### **常量**
- int DEC, HEX, OCT   
*进制*

- int left_align, right_align, non_align  
*是否有对齐要求:left_align左对齐，right_align右对齐，non_align无对齐要求(default)*

- size_t f, g, e  
*浮点数输出格式*

#### **变量**

- int alignment  宽度限制模式，left_align/right_align/non_align
- size_t align_width 格式化：宽度
- int numsystem  进制，DEC/HEX/OCT
- bool upperHEX 16进制是否需要大写
- size_t len_kept 小数保留位数
- size_t f_type 浮点数输出格式,f/g/e

### _Tp

#### **可调用常量**

- size_t str, fmt  
记录存储是格式串还是字符串 
- int INT, SHORT, LONG, LONGLONG, FLOAT, DOUBLE, LONGDOUBLE
类型对应数值，若为负值则为unsigned版


#### **函数(public)**

$\color{red}\text{@表示调用条件错误时抛出异常}$

- _Tp(size_t, int/string, splim) 初始化，参数从左到右为：类型、内容、（若为fmt）特殊限制
- size_t type() 返回类型
- int name () @返回数据类型对应常量
- size_t content (char *) @将字符串存入参数中并返回其长度
- int align_limit() 返回对齐情况
- size_t align_width() @有对齐时返回对齐长度
- int number_system () @返回整数进制
- bool isupper_HEX() @返回16进制的大小写状态，真为大写假为小写
- size_t decimals_kept() @返回浮点数保留小数位数
- size_t fopt() @返回浮点数%f/g/e对应常量
