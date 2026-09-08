#include <stdio.h>
#include <stdlib.h>

#define PRICE 8

// 对书的数量排序函数（从大到小）
int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

// 计算最小总价格的贪心算法
double calculate_min_price(int books[5]) {
    int counts[5];
    for (int i = 0; i < 5; i++) {
        counts[i] = books[i];
    }

    double total_price = 0.0;
    double discount[] = {0.75, 0.8, 0.9, 0.95}; // 折扣比例

    while (1) {
        qsort(counts, 5, sizeof(int), compare);

        int distinct_books = 0;
        for (int i = 0; i < 5; i++) {
            if (counts[i] > 0) {
                distinct_books++;
            } else {
                break;
            }
        }

        if (distinct_books == 0) {
            break;
        }

        switch (distinct_books) {
            case 5:
                total_price += 5 * PRICE * discount[0];
                for (int i = 0; i < 5; i++) {
                    counts[i]--;
                }
                break;
            case 4:
                total_price += 4 * PRICE * discount[1];
                for (int i = 0; i < 4; i++) {
                    counts[i]--;
                }
                break;
            case 3:
                total_price += 3 * PRICE * discount[2];
                for (int i = 0; i < 3; i++) {
                    counts[i]--;
                }
                break;
            case 2:
                total_price += 2 * PRICE * discount[3];
                for (int i = 0; i < 2; i++) {
                    counts[i]--;
                }
                break;
            case 1:
                total_price += PRICE;
                counts[0]--;
                break;
        }
    }

    return total_price;
}

int main() {
    int books[5];

    printf("请依次输入这五卷购买的本数：\n");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &books[i]);
    }

    double min_price = calculate_min_price(books);
    printf("购买这批书的最低价格为: %.2f欧元\n", min_price);

    return 0;
}


