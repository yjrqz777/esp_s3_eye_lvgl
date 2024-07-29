#include <stdio.h>  
  
// 定义gcd函数  
int gcd(int a, int b) {  
    int c;  
    while (b != 0) {  
        c = a % b;  
        a = b;  
        b = c;  
    }  
    return a;  
}  
  
int main() {  
    int m, n;  
    printf("请输入两个正整数m和n: ");  
    scanf("%d%d", &m, &n);  
  
    printf("%d和%d的最大公约数是: %d\n", m, n, gcd(m, n));  
    return 0;  
}