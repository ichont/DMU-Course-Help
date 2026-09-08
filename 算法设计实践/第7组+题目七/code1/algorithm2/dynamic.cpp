#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PRICE 8
#define INF 9999

int book[5];
double discount[4] = {0.75, 0.8, 0.9, 0.95};
double dp[10][10][10][10][10];

double min_price(double t1, double t2, double t3, double t4, double t5) {
    double min = t1;
    if (t2 < min) min = t2;
    if (t3 < min) min = t3;
    if (t4 < min) min = t4;
    if (t5 < min) min = t5;
    return min;
}

int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

void calculate_min_price() {
    memset(dp, 0, sizeof(dp));
    qsort(book, 5, sizeof(int), compare);
    
    for (int i = 0; i <= book[4]; ++i) {
        for (int j = i; j <= book[3]; ++j) {
            for (int k = j; k <= book[2]; ++k) {
                for (int l = k; l <= book[1]; ++l) {
                    for (int m = l; m <= book[0]; ++m) {
                        if (i + j + k + l + m == 0) {
                            continue;
                        }

                        double t1 = INF, t2 = INF, t3 = INF, t4 = INF, t5 = INF;
                        if (i >= 1) {
                            int num[5] = {m - 1, l - 1, k - 1, j - 1, i - 1};
                            qsort(num, 5, sizeof(int), compare);
                            t1 = 5 * PRICE * discount[0] + dp[num[0]][num[1]][num[2]][num[3]][num[4]];
                        }
                        if (j >= 1) {
                            int num[5] = {m - 1, l - 1, k - 1, j - 1, i};
                            qsort(num, 5, sizeof(int), compare);
                            t2 = 4 * PRICE * discount[1] + dp[num[0]][num[1]][num[2]][num[3]][num[4]];
                        }
                        if (k >= 1) {
                            int num[5] = {m - 1, l - 1, k - 1, j, i};
                            qsort(num, 5, sizeof(int), compare);
                            t3 = 3 * PRICE * discount[2] + dp[num[0]][num[1]][num[2]][num[3]][num[4]];
                        }
                        if (l >= 1) {
                            int num[5] = {m - 1, l - 1, k, j, i};
                            qsort(num, 5, sizeof(int), compare);
                            t4 = 2 * PRICE * discount[3] + dp[num[0]][num[1]][num[2]][num[3]][num[4]];
                        }
                        if (m >= 1) {
                            int num[5] = {m - 1, l, k, j, i};
                            qsort(num, 5, sizeof(int), compare);
                            t5 = PRICE + dp[num[0]][num[1]][num[2]][num[3]][num[4]];
                        }

                        dp[m][l][k][j][i] = min_price(t1, t2, t3, t4, t5);
                    }
                }
            }
        }
    }
}

double get_min_price() {
    return dp[book[0]][book[1]][book[2]][book[3]][book[4]];
}

int main() {
	printf("请依次输入这五卷购买的本数：\n");
    for (int i = 0; i < 5; ++i) {
        scanf("%d", &book[i]);
    }

    calculate_min_price();
    printf("购买这批书的最低价格为: %.2f欧元\n", get_min_price());

    return 0;
}

