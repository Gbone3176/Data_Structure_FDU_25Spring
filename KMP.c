#include <stdio.h>
#include <string.h>

// 构造 next 数组（next[0] = -1 的特殊实现）
void buildNext(const char* pattern, int* next, int pattern_len) {
    next[0] = -1;
    int j = -1;
    int i = 0;
    
    while (i < pattern_len - 1) {
        // j = -1 是初始条件，或者当前字符与前缀字符匹配
        if (j == -1 || pattern[i] == pattern[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            // 不匹配时，j回退
            j = next[j];
        }
    }
}

// KMP 字符串匹配算法
int kmpSearch(const char* text, const char* pattern) {
    int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    
    // 特殊情况处理
    if (pattern_len == 0) return 0;
    if (text_len < pattern_len) return -1;
    
    // 构造 next 数组
    int next[pattern_len];
    buildNext(pattern, next, pattern_len);
    
    // 打印 next 数组（用于调试）
    printf("Next 数组: ");
    for (int i = 0; i < pattern_len; i++) {
        printf("%d ", next[i]);
    }
    printf("\n");
    
    // 开始匹配
    int i = 0; // 文本指针
    int j = 0; // 模式指针
    
    while (i < text_len && j < pattern_len) {
        if (j == -1 || text[i] == pattern[j]) {
            // 当前字符匹配成功或 j = -1（需要右移模式串）
            i++;
            j++;
        } else {
            // 匹配失败，模式指针回退
            j = next[j];
        }
    }
    
    // 判断是否找到匹配
    if (j == pattern_len) {
        return i - j; // 返回匹配起始位置
    } else {
        return -1; // 未找到匹配
    }
}

int main() {
    char pattern[] = "ABCABCDABABCACBAC";
    int pattern_len = strlen(pattern);
    int next[pattern_len];
    
    // 构造并打印 next 数组
    buildNext(pattern, next, pattern_len);
    
    printf("模式串: %s\n", pattern);
    printf("索引:   ");
    for (int i = 0; i < pattern_len; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    printf("next:   ");
    for (int i = 0; i < pattern_len; i++) {
        printf("%d ", next[i]);
    }
    printf("\n");
    
    // 测试匹配
    char text[] = "ABABCABCDABABCACBACDEF";
    int pos = kmpSearch(text, pattern);
    
    if (pos != -1) {
        printf("找到匹配，起始位置: %d\n", pos);
    } else {
        printf("未找到匹配\n");
    }
    
    return 0;
}