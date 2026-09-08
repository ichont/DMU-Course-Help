#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define maxn 100

int a[maxn], b[maxn], c[maxn];

// 递归函数，计算最长不降子序列的长度
int longestIncreasingSubsequence(int i, int n) {
    if (b[i] != -1) // 如果已经计算过该位置的最长不降子序列长度，则直接返回结果
        return b[i];

    int max = 1, p = 0;
    for (int j = i + 1; j <= n; j++) {
        if (a[i] <= a[j]) {
            int len = longestIncreasingSubsequence(j, n) + 1; // 递归计算以a[j]开头的最长不降子序列长度
            if (len > max) {
                max = len;
                p = j;
            }
        }
    }
    b[i] = max; // 记录当前位置的最长不降子序列长度
    c[i] = p;   // 记录当前位置最长不降子序列的下一个元素的索引
    return max;
}

// 输出最长不降子序列
void printLongestIncreasingSubsequence(int p) {
    if (p == 0) // 递归基，当p为0时，结束递归
        return;
    printf("%d ", a[p]);
    printLongestIncreasingSubsequence(c[p]); // 递归调用，输出下一个元素
}

int main() {
    int n;

    printf("请输入序列中的元素个数: ");
    scanf("%d", &n);

    // 输入序列
    printf("请输入序列: ");
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    // 初始化b和c数组
    for (int i = 1; i <= n; i++) {
        b[i] = -1; // 初始化为-1，表示未计算过
        c[i] = 0;
    }

    // 计算最长不降子序列的长度
    int max = 0, startIndex = 0;
    for (int i = 1; i <= n; i++) {
        int len = longestIncreasingSubsequence(i, n);
        if (len > max) {
            max = len;
            startIndex = i;
        }
    }

    // 输出最长不降子序列的长度和序列本身
    printf("最长不降子序列长度为: %d\n", max);
    printf("最长不降子序列为:\n");
    printLongestIncreasingSubsequence(startIndex);

    return 0;
}