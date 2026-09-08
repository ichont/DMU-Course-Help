#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

int student_number = 0; // 记录学生实际人数全局变量
int num = 1;         // 程序的主控制变量
int choice = -1;     // 功能函数控制变量

void Menu();                 // 显示菜单
void Exit();                 // 退出程序
void Append_record(STU** head); // 从键盘输入一个学生信息
void List_record(STU* head);    // 输出学生信息
void Delete_record(STU** head); // 指定学号或姓名删除一个学生信息
void Modify_record(STU* head);  // 指定学号或姓名修改一个学生信息
void Search_record(STU* head);  // 按照学号或姓名查找相关学生信息
void Sort_Bubble(STU** head, int type); // 按照总分降序或学号降序排序（冒泡法）type = 1为按照总分降序排序，type = 2为按照学号降序排序
void Sort_Select(STU** head, int type); // 按照总分升序或学号升序排序（选择法）type = 1为按照总分升序排序，type = 2为按照学号升序排序
void Write(STU* head);      // 将输入学生信息保存到student.dat文件中
void Read(STU** head);      // 从文件中读取全部学生信息或从文件中随机读取某个学生的信息(指定学号或姓名)
void Insert(STU** head);    // 按照总成绩由高到低进行直接插入排序

int main() {
    STU* head = NULL;
    char input[15];

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
        case 1: Append_record(&head); break;
        case 2: List_record(head); break;
        case 3: Delete_record(&head); break;
        case 4: Modify_record(head); break;
        case 5: Search_record(head); break;
        case 6: Sort_Bubble(&head, 1); break;    // type = 1为按照总分降序排序
        case 7: Sort_Select(&head, 1); break;    // type = 1为按照总分升序排序，
        case 8: Sort_Bubble(&head, 2); break;    // type = 2为按照学号降序排序
        case 9: Sort_Select(&head, 2); break;    // type = 2为按照学号升序排序
        case 10: Write(head); break;
        case 11: Read(&head); break;
        case 12: Insert(&head); break;
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

}

// 退出程序函数
void Exit() {
    printf("\n退出程序\n");
    num = 0;
}

// 添加学生信息函数
void Append_record(STU** head) {
    if (student_number >= N) {
        printf("学生数量已满，无法添加新学生。\n");
        return;
    }

    STU* new_student = (STU*)malloc(sizeof(STU));
    if (new_student == NULL) {
        printf("内存分配失败！\n");
        return;
    }
    new_student->next = NULL;

    printf("请输入学生的信息!\n");

    printf("请输入学号: ");
    scanf("%s", new_student->num);

    // 判断添加学生学号是否与现有学生学号重复
    STU* temp = *head;
    while (temp != NULL) {
        if (strcmp(temp->num, new_student->num) == 0) {
            printf("学号重复，输入错误！\n");
            free(new_student); // 释放新分配的内存
            return;
        }
        temp = temp->next;
    }

    printf("请输入姓名: ");
    scanf("%s", new_student->name);

    printf("请输入专业: ");
    scanf("%s", new_student->major);
    // 判断专业是否为（computer，software，network）中的其中一个
    while (strcmp(new_student->major, "computer") != 0 &&
        strcmp(new_student->major, "software") != 0 &&
        strcmp(new_student->major, "network") != 0) {
        printf("专业（computer，software，network）输入错误！请重新输入：");
        scanf("%s", new_student->major);
    }

    printf("请输入班级: ");
    scanf("%d", &new_student->classNo);
    // 判断班级（classNo）是否为1-2
    while (new_student->classNo < 1 || new_student->classNo > 2) {
        printf("班级（1-2）输入错误！请重新输入：");
        scanf("%d", &new_student->classNo);
    }

    new_student->sum = 0;
    for (int j = 0; j < M; j++) {
        printf("请输入第%d科成绩: ", j + 1);
        scanf("%d", &new_student->score[j]);
        // 判断成绩（score）是否正常（0-100）
        while (new_student->score[j] < 0 || new_student->score[j] > 100) {
            printf("成绩（0-100）输入错误！请重新输入：");
            scanf("%d", &new_student->score[j]);
        }
        new_student->sum += new_student->score[j];
    }

    if (*head == NULL) {
        *head = new_student;
    }
    else {
        temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_student;
    }

    student_number++;

    printf("\n");
    printf("输入成功！\n");
}


// 输出学生信息函数
void List_record(STU* head) {
    if (head == NULL) {
        printf("无学生信息可输出。\n");
        return;
    }
    STU* temp = head;
    while (temp != NULL) {
        printf("学号: %s, 姓名: %s, 专业: %s, 班级: %d, 成绩: %d, %d, %d, 总分: %d\n",
            temp->num, temp->name, temp->major, temp->classNo,
            temp->score[0], temp->score[1], temp->score[2], temp->sum);
        temp = temp->next;
    }
}

// 删除学生信息函数（指定学号或姓名）
void Delete_record(STU** head) {
    if (*head == NULL) {
        printf("没有学生信息！\n");
        return;
    }
    char id[15];
    printf("请输入要删除的学生学号或姓名: ");
    scanf("%s", id);

    STU* temp = *head;
    STU* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->num, id) == 0 || strcmp(temp->name, id) == 0) {
            if (prev == NULL) {
                *head = temp->next;
            }
            else {
                prev->next = temp->next;
            }
            free(temp);
            student_number--;
            printf("学生信息删除成功！\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("未找到指定学生。\n");
}


// 修改学生信息函数（指定学号或姓名）
void Modify_record(STU* head) {
    if (head == NULL) {
        printf("没有学生信息！\n");
        return;
    }

    char id[15];
    printf("请输入要修改的学生学号或姓名: ");
    scanf("%s", id);

    STU* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->num, id) == 0 || strcmp(temp->name, id) == 0) {
            char new_num[15];
            printf("请输入新的学号: ");
            scanf("%s", new_num);
            // 判断添加学生学号是否与现有学生学号重复
            STU* tp = head;
            while (tp != NULL) {
                if (strcmp(tp->num, new_num) == 0) {
                    printf("学号重复，输入错误！\n");
                    return;
                }
                tp = tp->next;
            }
            strcpy(temp->num, new_num);

            printf("请输入新的姓名: ");
            scanf("%s", temp->name);

            printf("请输入新的专业: ");
            scanf("%s", temp->major);
            // 判断专业是否为（computer，software，network）中的其中一个
            while (strcmp(temp->major, "computer") != 0 &&
                strcmp(temp->major, "software") != 0 &&
                strcmp(temp->major, "network") != 0) {
                printf("专业（computer，software，network）输入错误！请重新输入：");
                scanf("%s", temp->major);
            }

            printf("请输入新的班级: ");
            scanf("%d", &temp->classNo);
            // 判断班级（classNo）是否为1-2
            while (temp->classNo < 1 || temp->classNo > 2) {
                printf("班级（1-2）输入错误！请重新输入：");
                scanf("%d", &temp->classNo);
            }

            temp->sum = 0;
            for (int j = 0; j < M; j++) {
                printf("请输入第%d科成绩: ", j + 1);
                scanf("%d", &temp->score[j]);
                // 判断成绩（score）是否正常（0-100）
                while (temp->score[j] < 0 || temp->score[j] > 100) {
                    printf("成绩（0-100）输入错误！请重新输入：");
                    scanf("%d", &temp->score[j]);
                }
                temp->sum += temp->score[j];
            }
            printf("学生信息修改成功！\n");
            return;
        }
        temp = temp->next;
    }
    printf("未找到指定的学生信息！\n");
}

// 查找相关学生信息（按照学号或姓名）
void Search_record(STU* head) {
    if (head == NULL) {
        printf("没有学生信息！\n");
        return;
    }

    char id[15];
    printf("请输入要查找的学生学号或姓名: ");
    scanf("%s", id);

    STU* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->num, id) == 0 || strcmp(temp->name, id) == 0) {
            printf("学号: %s, 姓名: %s, 专业: %s, 班级: %d, 成绩: %d, %d, %d, 总成绩: %d\n",
                temp->num, temp->name, temp->major, temp->classNo,
                temp->score[0], temp->score[1], temp->score[2], temp->sum);
            return;
        }
        temp = temp->next;
    }

    printf("未找到指定的学生信息！\n");
}

// 冒泡排序 type = 1为按照总分降序排序，type = 2为按照学号降序排序
void Sort_Bubble(STU** head, int type) {
    if (*head == NULL) {
        printf("没有学生信息！\n");
        return;
    }

    int swapped;
    STU* ptr1;
    STU* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            int condition = (type == 1) ? (ptr1->sum < ptr1->next->sum) : (strcmp(ptr1->num, ptr1->next->num) < 0);
            if (condition) {
                // 交换节点数据
                char tempNum[20], tempName[20], tempMajor[20];
                int tempClassNo, tempScore[3], tempSum;

                // 交换学号
                strcpy(tempNum, ptr1->num);
                strcpy(ptr1->num, ptr1->next->num);
                strcpy(ptr1->next->num, tempNum);

                // 交换姓名
                strcpy(tempName, ptr1->name);
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->next->name, tempName);

                // 交换专业
                strcpy(tempMajor, ptr1->major);
                strcpy(ptr1->major, ptr1->next->major);
                strcpy(ptr1->next->major, tempMajor);

                // 交换班级
                tempClassNo = ptr1->classNo;
                ptr1->classNo = ptr1->next->classNo;
                ptr1->next->classNo = tempClassNo;

                // 交换成绩
                for (int i = 0; i < 3; i++) {
                    tempScore[i] = ptr1->score[i];
                    ptr1->score[i] = ptr1->next->score[i];
                    ptr1->next->score[i] = tempScore[i];
                }

                // 交换总分
                tempSum = ptr1->sum;
                ptr1->sum = ptr1->next->sum;
                ptr1->next->sum = tempSum;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    printf("排序完成！\n");
}


// 选择排序 type = 1为按照总分升序排序，type = 2为按照学号升序排序
void Sort_Select(STU** head, int type) {
    if (*head == NULL) {
        printf("没有学生信息！\n");
        return;
    }

    STU* i = *head;
    while (i != NULL) {
        STU* min = i;
        for (STU* j = i->next; j != NULL; j = j->next) {
            int condition = (type == 1) ? (j->sum < min->sum) : (strcmp(j->num, min->num) < 0);
            if (condition) {
                min = j;
            }
        }
        if (min != i) {
            // 交换两个节点的数据
            STU temp = *i;
            *i = *min;
            *min = temp;

            // 交换next指针
            STU* tempNext = min->next;
            min->next = i->next;
            i->next = tempNext;
        }
        i = i->next;
    }
    printf("排序完成！\n");
}


//// 使用二进制数据文件"student.dat"
//// 将学生信息保存到文件中
//void Write(STU* head) {
//    FILE* file = fopen("student.dat", "wb");
//    if (!file) {
//        printf("无法打开文件！\n");
//        return;
//    }
//
//    STU* temp = head;
//    while (temp != NULL) {
//        fwrite(temp, sizeof(STU), 1, file);
//        temp = temp->next;
//    }
//
//    fclose(file);
//    printf("学生信息保存成功！\n");
//}
//
//// 从文件中读取学生信息
//void Read(STU** head) {
//    FILE* file = fopen("student.dat", "rb");
//    if (!file) {
//        printf("无法打开文件！\n");
//        return;
//    }
//
//    STU* temp = NULL;
//    while (!feof(file)) {
//        STU* new_student = (STU*)malloc(sizeof(STU));
//        if (fread(new_student, sizeof(STU), 1, file)) {
//            new_student->next = NULL;
//
//            if (*head == NULL) {
//                *head = new_student;
//                temp = *head;
//            }
//            else {
//                temp->next = new_student;
//                temp = temp->next;
//            }
//
//            student_number++;
//        }
//        else {
//            free(new_student);
//        }
//    }
//
//    fclose(file);
//    printf("学生信息读取成功！\n");
//}


// 使用文本文件"student.txt"
// 将学生信息保存到文件中
void Write(STU* head) {
    FILE* file = fopen("student.txt", "w");
    if (file == NULL) {
        printf("文件打开失败，未找到指定文件。\n");
        return;
    }

    STU* temp = head;
    while (temp != NULL) {
        fprintf(file, "%s %s %s %d %d %d %d %d\n",
            temp->num, temp->name, temp->major, temp->classNo,
            temp->score[0], temp->score[1], temp->score[2], temp->sum);
        temp = temp->next;
    }

    fclose(file);
    printf("学生信息保存成功！\n");
}
// 从文件中读取学生信息
void Read(STU** head) {
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

    STU* last = NULL;
    int found = 0;

    while (1) {
        STU* new_node = (STU*)malloc(sizeof(STU));
        if (fscanf(fp, "%s %s %s %d %d %d %d %d",
            new_node->num, new_node->name,
            new_node->major, &new_node->classNo,
            &new_node->score[0], &new_node->score[1],
            &new_node->score[2], &new_node->sum) == EOF) {
            free(new_node);
            break;
        }

        if (search_mode == 1 ||
            strcmp(new_node->num, id) == 0 ||
            strcmp(new_node->name, id) == 0) {
            if (*head == NULL) {
                *head = new_node;
            }
            else {
                last->next = new_node;
            }
            last = new_node;
            last->next = NULL;
            found = 1;
        }
        else {
            free(new_node);
        }
    }

    fclose(fp);

    if (found) {
        printf("读取成功。\n");
        List_record(*head);
    }
    else {
        printf("未找到指定学生信息。\n");
    }
}

// 直接插入排序（按照总成绩降序）
void Insert(STU** head) {
    if (*head == NULL || (*head)->next == NULL) {
        printf("没有足够的学生信息进行排序！\n");
        return;
    }

    STU* sorted = NULL;
    STU* current = *head;

    while (current != NULL) {
        STU* next = current->next;

        if (sorted == NULL || sorted->sum <= current->sum) {
            current->next = sorted;
            sorted = current;
        }
        else {
            STU* temp = sorted;
            while (temp->next != NULL && temp->next->sum > current->sum) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }

    *head = sorted;
    printf("直接插入排序完成！\n");
}