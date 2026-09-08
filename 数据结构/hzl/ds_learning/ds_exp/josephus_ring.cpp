//#define _CRT_SECURE_NO_WARNINGS
//
//#include <iostream>
//#include <queue>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//using namespace std;
//
////josephus_ring(约瑟夫环问题)
//
////解法一：数组实现
//
//int array_find(int n, int m) {
//
//    int arr[100] = { 0 };
//    int count = 0;
//    int i = 0, k = 0;
//
//    while (count != n - 1) {
//        i++;
//        if (i > n) {
//            i = 1;
//        }
//        if (arr[i] == 0) {
//            k++;
//            if (k == m) {
//                arr[i] = 1;
//                count++;
//                k = 0;
//            }
//        }
//    }
//    for (i = 1; i < n; i++) {
//        if (arr[i] == 0) {
//            return i;
//        }
//    }
//    return 0;
//}
//
////解法二:链表实现
//
//typedef struct header
//{
//    int length;
//    struct node* next;
//}head;
//typedef struct node
//{
//    int val;
//    struct node* next;
//}node;
//head* listcreat()
//{
//    head* p;
//    p = (head*)malloc(sizeof(head));
//    p->next = NULL;
//    p->length = 0;
//    return p;
//}
//void listinsert(head* p, int pos, int x)
//{
//    if (p == NULL || pos<0 || pos>p->length)
//    {
//        printf("listinsert():error\n");
//        return;
//    }
//    node* temp = (node*)malloc(sizeof(node));
//    temp->val = x;
//    node* pcur = p->next;//指向第一个数据节点
//    node* plast = p->next;//指向最后一个数据节点
//    while (pcur != NULL && plast->next != pcur)//使plast指向最后一个节点
//    {
//        plast = plast->next;
//    }
//    if (p->length == 0)//判断循环链表为空的情况
//    {
//        p->next = temp;
//        temp->next = temp;
//    }
//    else if (pos == 0)//头插
//    {
//        plast->next = temp;
//        temp->next = pcur;
//        p->next = temp;
//    }
//    else if (pos == p->length)//尾插
//    {
//        plast->next = temp;
//        temp->next = pcur;
//    }
//    else
//    {
//        node* pval = p->next;//pval用来指向要插入位置的数据节点
//        for (int i = 1; i < pos; i++)
//        {
//            pval = pval->next;
//        }
//        temp->next = pval->next;
//        pval->next = temp;
//    }
//    p->length++;
//    return;
//}
//void listdelete(head* p, int x)
//{
//    node* temp;//temp指向要删除的节点
//    temp = p->next;
//    for (int i = 0; i < p->length; i++)
//    {
//        if (temp->val == x)
//        {
//            break;
//        }
//        temp = temp->next;
//    }
//    node* pcur = p->next;//pcur指向第一个节点
//    node* plast = p->next;//plast用来指向最后一个节点
//    while (plast->next != pcur)
//    {
//        plast = plast->next;
//    }
//    if (temp->val != x)
//    {
//        printf("listprintf():error\n");
//        return;
//    }
//    if (p->length == 1)//只有一个元素时
//    {
//        p->next = NULL;
//    }
//    else if (temp == pcur)//删除的是第一个节点
//    {
//        p->next = pcur->next;
//        plast->next = pcur->next;
//    }
//    else if (temp == plast)//删除的是最后一个节点
//    {
//        node* pre = p->next;//指向倒数第二个节点
//        while (pre->next != plast)
//        {
//            pre = pre->next;
//        }
//        pre->next = pcur;
//    }
//    else
//    {
//        node* pre = p->next;
//        while (pre->next != temp)//使pre指向temp的前一个元素
//        {
//            pre = pre->next;
//        }
//        pre->next = temp->next;
//    }
//    p->length--;
//}
//void listprint(head* p)
//{
//    if (p == NULL || p->length == 0)
//    {
//        printf("listprint():error");
//        return;
//    }
//    node* temp = p->next;
//    for (int i = 0; i < p->length; i++)
//    {
//        printf("%d ", temp->val);
//        temp = temp->next;
//    }
//    printf("\n");
//    return;
//}
//void Llist_find(int n, int m)
//{
//    head* p;
//    p = listcreat();
//    for (int i = n; i > 0; i--)
//    {
//        listinsert(p, 0, i);
//    }
//    listprint(p);
//    node* temp = p->next;
//    int count = 1;
//    printf("被踢顺序\n");
//    while (temp->next != temp)//剩下一个数时结束循环
//    {
//        if (count == m)
//        {
//            node* pre = p->next;
//            while (pre->next != temp)//指向temp的前一个节点
//            {
//                pre = pre->next;
//            }
//            printf("%d ", temp->val);
//            listdelete(p, temp->val);
//            temp = pre;
//            count = 0;
//            continue;
//        }
//        count++;
//        temp = temp->next;
//    }
//    printf("\n");
//    printf("链表中最后被剩下的是：\n");
//    listprint(p);
//}
//
//
////解法三:队列实现
//
//queue<int> res;
//
//void queue_find(int n, int m) {
//    for (int i = 1; i <= n; i++)
//    {
//        res.push(i);
//    }
//    int cnt = 0;
//    while (!res.empty())
//    {
//        for (int i = 1; i <= m - 1; i++)//执行k-1次
//        {
//            res.push(res.front());//将队首元素放队尾去
//            res.pop();
//        }
//        //循环结束后输出队首元素
//        cout << res.front() << " ";
//        res.pop();//出列
//    }
//}
//
////解法四:正向递归
//int recursion_find(int n, int m) {
//    int thelast = 0;
//    if (n == 1) {
//        return 0;
//    }
//    return ((recursion_find(n - 1, m) + m) % n);
//}
//
//
////解法五:反向迭代
//int iteration_find(int n, int m) {
//    int thelast = 0;
//    for (int i = 2; i <= n; ++i) {
//        thelast = (thelast + m) % i;
//    }
//
//    return thelast;
//}
//
//
//
//int main() {
//    int n, m;
//    do {
//        cout << "请输入先后分别总个数n以及报数间隔m：(输入0 0退出程序)" << endl;
//        cin >> n >> m;
//        if (n == 0 && m == 0) {
//            break;
//        }
//        if (n < 0 || m < 0) {
//            cout << "非法数字输入，请重新输入" << endl;
//            continue;
//        }
//        cout << "请选择实现方法：" << endl
//            << "输入“1”数组实现" << endl
//            << "输入“2”链表实现" << endl
//            << "输入“3”队列实现" << endl
//            << "输入“4”正向递归" << endl
//            << "输入“5”反向迭代" << endl;
//        int x = 0;
//        int thelast = 0;
//        cin >> x;
//        switch (x) {
//        case 1:
//            thelast = array_find(n, m);
//            cout << "最后留下的“thelast”的编号是：" << thelast << endl;
//            break;
//        case 2:
//            Llist_find(n, m);
//            break;
//        case 3:
//            queue_find(n, m);
//            break;
//        case 4:
//            // 因为编号是从1开始的而非0，所以thelast的编号需要加1
//            thelast = recursion_find(n, m) + 1;
//            cout << "最后留下的“thelast”的编号是：" << thelast << endl;
//            break;
//        case 5:
//            // 因为编号是从1开始的而非0，所以thelast的编号需要加1
//            thelast = iteration_find(n, m) + 1;
//            cout << "最后留下的“thelast”的编号是：" << thelast << endl;
//            break;
//        }
//    } while (1);
//    return 0;
//}
//
//

