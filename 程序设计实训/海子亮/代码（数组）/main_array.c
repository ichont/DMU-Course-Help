#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "student.h"

int sum[N] = { 0 };         // 学生总成绩全局数组
int student_number = 0;     // 记录学生实际人数全局变量
int num = 1;         // 程序的主控制变量
int choice = -1;     // 功能函数控制变量+

void Menu();                 // 显示菜单
void Exit();                 // 退出程序
void Append_record(STU* st); // 从键盘输入一个学生信息
void List_record(STU* st);   // 输出学生信息
void Delete_record(STU* st); // 指定学号或姓名删除一个学生信息
void Modify_record(STU* st); // 指定学号或姓名修改一个学生信息
void Search_record(STU* st); // 按照学号或姓名查找相关学生信息
void Sort_Bubble(STU* st, int type); // 按照总分降序或学号降序排序（冒泡法）type = 1为按照总分降序排序，type = 2为按照学号降序排序
void Sort_Select(STU* st, int type); // 按照总分升序或学号升序排序（选择法）type = 1为按照总分升序排序，type = 2为按照学号升序排序
void Write(STU* st);         // 将输入学生信息保存到student.dat文件中
void Read(STU* st);          // 从文件中读取全部学生信息或从文件中随机读取某个学生的信息(指定学号或姓名)
void Insert(STU* st);        // 按照总成绩由高到低进行直接插入排序

int main() {
    STU students[N];
    char input[15] = { 0 };

    while (num) {
        Menu();
        printf("***请输入功能序号，执行相应功能：");
        scanf("%s", &input);
        choice = atoi(input); // 将输入的字符串转换为整数

        if (choice == 0 && input[0] != '0') { // 检查输入的有效性
            printf("\n");
            printf("输入有误，请重新输入！\n");
            printf("\n");
            continue;
        }
        printf("***********************************************************\n");
        printf("\n");
        printf("\n");

        switch (choice) {
        case 0: Exit(); break;
        case 1: Append_record(students); break;
        case 2: List_record(students); break;
        case 3: Delete_record(students); break;
        case 4: Modify_record(students); break;
        case 5: Search_record(students); break;
        case 6: Sort_Bubble(students, 1); break;    // type = 1为按照总分降序排序
        case 7: Sort_Select(students, 1); break;    // type = 1为按照总分升序排序，
        case 8: Sort_Bubble(students, 2); break;    // type = 2为按照学号降序排序
        case 9: Sort_Select(students, 2); break;    // type = 2为按照学号升序排序
        case 10: Write(students); break;
        case 11: Read(students); break;
        case 12: Insert(students); break;
        default: printf("输入有误，请重新输入！\n"); break;
        }
        printf("\n");
        printf("\n");
    }
    return 0;
}

// 显示功能菜单函数
void Menu() {
    printf("***********************************************************\n");
    printf("**************---欢迎使用学生信息管理系统----**************\n");
    printf("*****************----2220222043-海子亮----*****************\n");
    printf("***********************************************************\n");
    printf("***\t主菜单\t\t\t\t\t\t***\n");
    printf("***\t0.退出程序执行\t\t\t\t\t***\n");
    printf("***\t1.输入学生信息\t\t\t\t\t***\n");
    printf("***\t2.输出学生信息\t\t\t\t\t***\n");
    printf("***\t3.指定学号或姓名删除一个学生信息\t\t***\n");
    printf("***\t4.指定学号或姓名修改一个学生信息\t\t***\n");
    printf("***\t5.按照学号或姓名查找相关学生信息\t\t***\n");
    printf("***\t6.按照总分降序排序（冒泡法）\t\t\t***\n");
    printf("***\t7.按照总分升序排序（选择法）\t\t\t***\n");
    printf("***\t8.按照学号降序排序（冒泡法）\t\t\t***\n");
    printf("***\t9.按照学号升序排序（选择法）\t\t\t***\n");
    printf("***\t10.将输入学生信息保存到student.txt文件中\t***\n");
    printf("***\t11.从文件中读取全部学生或指定读取某个学生的信息\t***\n");
    printf("***\t12.按照总成绩由高到低进行直接插入排序。\t\t***\n");
    printf("***********************************************************\n");
    printf("***********************************************************\n");
    return;
}

// 退出程序函数
void Exit() {
    printf("\n退出程序\n");
    num = 0;
    return;
}

// 添加学生信息函数
void Append_record(STU* st) {
    if (student_number >= N) {
        printf("学生数量已满，无法添加新学生。\n");
        return;
    }

    printf("请输入第[%d]名学生的信息!\n", student_number + 1);

    printf("请输入学号: ");
    scanf("%s", st[student_number].num);

    // 判断添加学生学号是否与现有学生学号重复
    for (int i = 0; i < student_number; i++) {
        if (strcmp(st[i].num, st[student_number].num) == 0) {
            printf("学号重复，输入错误！");
            return;
        }
    }

    printf("请输入姓名: ");
    scanf("%s", st[student_number].name);

    printf("请输入专业: ");
    scanf("%s", st[student_number].major);
    // 判断专业是否为（computer，software，network）中的其中一个
    while (strcmp(st[student_number].major, "computer") != 0 &&
        strcmp(st[student_number].major, "software") != 0 &&
        strcmp(st[student_number].major, "network") != 0) {
        printf("专业（computer，software，network）输入错误！请重新输入：");
        scanf("%s", st[student_number].major);
    }

    printf("请输入班级: ");
    scanf("%d", &st[student_number].classNo);
    // 判断班级（classNo）是否为1-2
    while (st[student_number].classNo < 1 || st[student_number].classNo > 2) {
        printf("班级（1-2）输入错误！请重新输入：");
        scanf("%d", &st[student_number].classNo);
    }

    sum[student_number] = 0;
    for (int j = 0; j < M; j++) {
        printf("请输入第-%d-科成绩: ", j + 1);
        scanf("%d", &st[student_number].score[j]);
        // 判断成绩（score）是否正常（0-100）
        while (st[student_number].score[j] < 0 || st[student_number].score[j] > 100) {
            printf("成绩（0-100）输入错误！请重新输入：");
            scanf("%d", &st[student_number].score[j]);
        }
        sum[student_number] += st[student_number].score[j];
    }

    student_number++;

    printf("\n");
    printf("输入成功！");
    printf("\n");
    List_record(st);
}

// 输出学生信息函数
void List_record(STU* st) {
    if (student_number == 0) {
        printf("无学生信息可输出。\n");
        return;
    }
    for (int i = 0; i < student_number; i++) {
        printf("学号: %s, 姓名: %s, 专业: %s, 班级: %d, 成绩: %d, %d, %d,总分: %d\n",
            st[i].num, st[i].name, st[i].major, st[i].classNo,
            st[i].score[0], st[i].score[1], st[i].score[2], sum[i]);
    }
}

// 删除学生信息函数（指定学号或姓名）
void Delete_record(STU* st) {
    char id[15];
    printf("请输入要删除的学生学号或姓名: ");
    scanf("%s", id);

    for (int i = 0; i < student_number; i++) {
        if (strcmp(st[i].num, id) == 0 || strcmp(st[i].name, id) == 0) {
            printf("找到指定学生（第[%d]名）", i + 1);
            for (int j = i; j < student_number - 1; j++) {
                st[j] = st[j + 1];
                sum[j] = sum[j + 1];
            }
            student_number--;
            printf("删除成功，该学生后所有学生编号前移（减一）\n");
            List_record(st);
            return;
        }
    }
    printf("未找到指定学生。\n");
}

// 修改学生信息函数（指定学号或姓名）
void Modify_record(STU* st) {
    char id[15];        // 用户输入的标识符（学生学号或姓名）
    char tem_num[15];   // 暂时存放新的学生学号
    printf("请输入要修改的学生学号或姓名: ");
    scanf("%s", id);

    for (int i = 0; i < student_number; i++) {
        if (strcmp(st[i].num, id) == 0 || strcmp(st[i].name, id) == 0) {
            printf("请输入新的学生学号: ");
            scanf("%s", tem_num);
            // 判断添加的新学生学号是否与现有学生学号重复
            for (int j = 0; j < student_number; j++) {
                if (j == i) {
                    continue;
                }
                if (strcmp(st[j].num, tem_num) == 0) {
                    printf("学号重复，输入错误！");
                    return;
                }
            }

            strcpy(st[i].num, tem_num); // 无重复再修改

            printf("请输入新的学生姓名: ");
            scanf("%s", st[i].name);

            printf("请输入新的学生专业: ");
            scanf("%s", st[i].major);
            // 判断专业是否为（computer，software，network）中的其中一个
            while (strcmp(st[i].major, "computer") != 0 &&
                strcmp(st[i].major, "software") != 0 &&
                strcmp(st[i].major, "network") != 0) {
                printf("专业（computer，software，network）输入错误！请重新输入：");
                scanf("%s", st[i].major);
            }

            printf("请输入新的学生班级: ");
            scanf("%d", &st[i].classNo);
            // 判断班级（classNo）是否为1-2
            while (st[i].classNo < 1 || st[i].classNo > 2) {
                printf("班级（1-2）输入错误！请重新输入：");
                scanf("%d", &st[i].classNo);
            }

            sum[i] = 0;
            for (int j = 0; j < M; j++) {
                printf("请输入新的学生第-%d-科成绩: ", j + 1);
                scanf("%d", &st[i].score[j]);
                // 判断成绩（score）是否正常（0-100）
                while (st[i].score[j] < 0 || st[i].score[j] > 100) {
                    printf("成绩（0-100）输入错误！请重新输入：");
                    scanf("%d", &st[i].score[j]);
                }
                sum[i] += st[i].score[j];
            }
            printf("修改成功。\n");
            printf("学号: %s, 姓名: %s, 专业: %s, 班级: %d, 成绩: %d, %d, %d,总分: %d\n",
                st[i].num, st[i].name, st[i].major, st[i].classNo,
                st[i].score[0], st[i].score[1], st[i].score[2], sum[i]);
            return;
        }
    }
    printf("未找到指定学生。\n");
}

// 查找相关学生信息（按照学号或姓名）
void Search_record(STU* st) {
    char id[15];
    printf("请输入要查找的学生学号或姓名: ");
    scanf("%s", id);

    for (int i = 0; i < student_number; i++) {
        if (strcmp(st[i].num, id) == 0 || strcmp(st[i].name, id) == 0) {
            printf("找到指定学生（第[%d]名）\n", i + 1);
            printf("学号: %s, 姓名: %s, 专业: %s, 班级: %d, 成绩: %d, %d, %d,总分: %d\n",
                st[i].num, st[i].name, st[i].major, st[i].classNo,
                st[i].score[0], st[i].score[1], st[i].score[2], sum[i]);
            return;
        }
    }
    printf("未找到指定学生。\n");
}

// 冒泡排序 type = 1为按照总分降序排序，type = 2为按照学号降序排序
void Sort_Bubble(STU* st, int type) {
    int i, j;
    for (i = 0; i < student_number - 1; i++) {
        int swap = 0;
        for (j = 0; j < student_number - i - 1; j++) {
            if ((type == 1 && sum[j] < sum[j + 1]) ||   // 按总分降序
                (type == 2 && strcmp(st[j].num, st[j + 1].num) < 0)) {  // 按学号降序
                STU temp = st[j];
                st[j] = st[j + 1];
                st[j + 1] = temp;

                int temp_sum = sum[j];
                sum[j] = sum[j + 1];
                sum[j + 1] = temp_sum;

                swap = 1;
            }
        }
        if (!swap) break;   // 如果本轮没有交换，则数组已经有序，提前退出
    }
    List_record(st);
}

// 交换两个学生结构体
void Swap(STU* a, STU* b) {
    STU temp = *a;
    *a = *b;
    *b = temp;
}

// 交换两个总成绩
void SwapSum(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 分区函数
int Partition(STU* st, int low, int high, int type) {
    STU pivot = st[low];  // 选择第一个元素作为基准
    int pivot_sum = sum[low];
    int i = low, j = high;

    while (i < j) {
        // 从右向左找比基准小的元素
        while (i < j && ((type == 1 && sum[j] <= pivot_sum) || (type == 2 && strcmp(st[j].num, pivot.num) <= 0)))
            j--;
        if (i < j) {
            st[i] = st[j];
            sum[i] = sum[j];
            i++;
        }

        // 从左向右找比基准大的元素
        while (i < j && ((type == 1 && sum[i] >= pivot_sum) || (type == 2 && strcmp(st[i].num, pivot.num) >= 0)))
            i++;
        if (i < j) {
            st[j] = st[i];
            sum[j] = sum[i];
            j--;
        }
    }
    st[i] = pivot;  // 基准归位
    sum[i] = pivot_sum;
    return i;  // 返回基准的位置
}

// 快速排序递归函数
void QuickSort(STU* st, int low, int high, int type) {
    if (low < high) {
        int pivot = Partition(st, low, high, type);  // 分区
        QuickSort(st, low, pivot - 1, type);  // 对左半部分排序
        QuickSort(st, pivot + 1, high, type);  // 对右半部分排序
    }
}

// 排序接口函数
void Sort_Quick(STU* st, int type) {
    QuickSort(st, 0, student_number - 1, type);
    List_record(st);  // 排序后输出学生信息
}

// 选择排序 type = 1为按照总分升序排序，type = 2为按照学号升序排序
void Sort_Select(STU* st, int type) {
    int i, j;
    for (i = 0; i < student_number - 1; i++) {
        int min_idx = i;
        for (j = i + 1; j < student_number; j++) {
            if ((type == 1 && sum[j] < sum[min_idx]) || // 按总分升序
                (type == 2 && strcmp(st[j].num, st[min_idx].num) < 0)) {    // 按学号升序
                min_idx = j;
            }
        }
        if (min_idx != i) {
            STU temp = st[i];
            st[i] = st[min_idx];
            st[min_idx] = temp;

            int temp_sum = sum[i];
            sum[i] = sum[min_idx];
            sum[min_idx] = temp_sum;
        }
    }
    List_record(st);
}


// 使用二进制数据文件"student.dat"
//void Write(STU* st) {
//    FILE* fp = fopen("student.dat", "wb");
//    if (fp == NULL) {
//        printf("文件打开失败，未找到指定文件。\n");
//        return;
//    }
//    fwrite(st, sizeof(STU), student_number, fp);
//    fclose(fp);
//    printf("保存成功。\n");
//}
//
//void Read(STU* st) {
//    FILE* fp = fopen("student.dat", "rb");
//    if (fp == NULL) {
//        printf("文件打开失败，未找到指定文件。\n");
//        return;
//    }
//    student_number = fread(st, sizeof(STU), N, fp);
//    fclose(fp);
//    printf("读取成功。\n");
//    List_record(st);
//}


// 使用文本文件"student.txt"
void Write(STU* st) {
    FILE* fp = fopen("student.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败，未找到指定文件。\n");
        return;
    }
    for (int i = 0; i < student_number; i++) {
        fprintf(fp, "%s %s %s %d %d %d %d %d\n",
            st[i].num, st[i].name, st[i].major, st[i].classNo,
            st[i].score[0], st[i].score[1], st[i].score[2], sum[i]);
    }
    fclose(fp);
    printf("保存成功。\n");
}

void Read(STU* st) {
    FILE* fp = fopen("student.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败，未找到指定文件。\n");
        return;
    }

    char id[15];
    int search_mode;

    printf("请选择操作：1 - 读取全部学生信息，2 - 查找特定学生信息\n");
    scanf("%d", &search_mode);

    if (search_mode == 2) {
        printf("请输入要查找的学号或姓名：\n");
        scanf("%s", id);
    }

    student_number = 0;
    int found = 0;

    while (fscanf(fp, "%s %s %s %d %d %d %d %d",
        st[student_number].num, st[student_number].name,
        st[student_number].major, &st[student_number].classNo,
        &st[student_number].score[0], &st[student_number].score[1],
        &st[student_number].score[2], &sum[student_number]) != EOF) {

        if (search_mode == 1 ||
            strcmp(st[student_number].num, id) == 0 ||
            strcmp(st[student_number].name, id) == 0) {
            student_number++;
            found = 1;
        }
    }

    fclose(fp);

    if (found) {
        printf("读取成功。\n");
        List_record(st);
    }
    else {
        printf("未找到指定学生信息。\n");
    }
}

// 直接插入排序（按照总成绩降序）
void Insert(STU* st) {
    for (int i = 1; i < student_number; i++) {
        STU key = st[i];
        int sum_key = sum[i];
        int j = i - 1;
        while (j >= 0 && sum[j] < sum_key) {
            st[j + 1] = st[j];
            sum[j + 1] = sum[j];
            j--;
        }
        st[j + 1] = key;
        sum[j + 1] = sum_key;
    }
    List_record(st);
}
