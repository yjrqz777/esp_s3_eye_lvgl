
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h> // 为了使用 malloc 和 free  

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
int main() {  
    long long datetime = 20240315140346; 
    printf("%lld\n",datetime);
    uint16_t year = datetime / 10000000000;  
    uint8_t month = (datetime % 1000000000) / 100000000;  
    uint8_t day = (datetime % 100000000) / 1000000;  
    uint8_t hour = (datetime % 1000000) / 10000;  
    uint8_t minute = (datetime % 10000) / 100;  
    uint8_t second = datetime % 100;  
    printf("%d-%d-%d %d:%d:%d\n",year,month,day,hour,minute,second);
}

  
// int main() {  
//     char* str = "620\nzzuli-student";  
//     size_t len = strlen(str); // 获取字符串长度  
//     printf("%.*s\n", (int)len, str); // 输出整个字符串，包括其中的 \n  
//     return 0;  
// }