#include <stdio.h>
#include <string.h>
#include "myscanf.cpp"
#include "myprintf.cpp"

#define MAX_LEN 4096

//各种数据类型的变量
char c = '\0';
short s = 0;
int i = 0;
long long ll = 0;
float f = 0.0;
double d = 0.0;
char str[MAX_LEN] = "";
void *p = NULL;

//输入缓存区、输出缓存区
char in_buf[MAX_LEN], out_buf[MAX_LEN];

//输入格式控制字符串、输出格式控制字符串
char in_fmt[MAX_LEN], out_fmt[MAX_LEN];

//输入缓冲区当前位置、输出缓冲区当前位置
int in_idx, out_idx;

int main()
{
    gets(in_fmt);
    gets(out_fmt);
    gets(in_buf);

    /* Will be replaced by script during testing - Begin */
    myscanf(in_fmt, str, &i, &c);
    myprintf(out_fmt, str, i, c);
    /* Will be replaced by script during testing - End */

    puts(out_buf);
}
