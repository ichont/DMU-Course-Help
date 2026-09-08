#include <stdio.h>
#include <stdlib.h>

#define PRICE 8
#define INF 9999

int book[5];
double discount[4] = {0.75, 0.8, 0.9, 0.95};

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

double F(int y1, int y2, int y3, int y4, int y5) {
    if (y1 + y2 + y3 + y4 + y5 == 0)
        return 0;

    int num[5] = {y1, y2, y3, y4, y5};
    qsort(num, 5, sizeof(int), compare);

    double t1 = INF, t2 = INF, t3 = INF, t4 = INF, t5 = INF;
    if (num[4] >= 1) t1 = 5 * PRICE * discount[0] + F(num[0] - 1, num[1] - 1, num[2] - 1, num[3] - 1, num[4] - 1);
    if (num[3] >= 1) t2 = 4 * PRICE * discount[1] + F(num[0] - 1, num[1] - 1, num[2] - 1, num[3] - 1, num[4]);
    if (num[2] >= 1) t3 = 3 * PRICE * discount[2] + F(num[0] - 1, num[1] - 1, num[2] - 1, num[3], num[4]);
    if (num[1] >= 1) t4 = 2 * PRICE * discount[3] + F(num[0] - 1, num[1] - 1, num[2], num[3], num[4]);
    if (num[0] >= 1) t5 = PRICE + F(num[0] - 1, num[1], num[2], num[3], num[4]);

    return min_price(t1, t2, t3, t4, t5);
}

int main() {
	printf("请依次输入这五卷购买的本数：\n");
    for (int i = 0; i < 5; ++i) {
        scanf("%d", &book[i]);
    }
    qsort(book, 5, sizeof(int), compare);
    printf("购买这批书的最低价格为: %.2f欧元\n", F(book[0], book[1], book[2], book[3], book[4]));
    return 0;
}

