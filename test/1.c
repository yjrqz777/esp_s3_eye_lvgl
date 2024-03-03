
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h> // 为了使用 malloc 和 free  
int main() {  
    char result[100]; // 创建一个足够大的字符数组来存储最终的字符串  
    char* elements[] = {"620", "zzuli-student", "zzuli-inside", "zzuli-student"}; // 你的字符串数组  
    int numElements = sizeof(elements) / sizeof(elements[0]); // 计算数组中的元素数量  
  
    // 初始化结果字符串为空  
    result[0] = '\0';  
  
    // 使用循环将每个元素添加到结果字符串中，并在每个元素后面添加一个换行符  
    for (int i = 0; i < numElements; i++) {  
        strcat(result, elements[i]);  
        strcat(result, "\n");  
    }  
  
    // 打印结果字符串  
    printf("%s\n", result);  
    // size_t len = strlen(result); // 获取字符串长度  
    // printf("%.*s", (int)len, result); // 输出整个字符串，包括其中的 \n  
    return 0;  
}

  
// int main() {  
//     char* str = "620\nzzuli-student";  
//     size_t len = strlen(str); // 获取字符串长度  
//     printf("%.*s\n", (int)len, str); // 输出整个字符串，包括其中的 \n  
//     return 0;  
// }