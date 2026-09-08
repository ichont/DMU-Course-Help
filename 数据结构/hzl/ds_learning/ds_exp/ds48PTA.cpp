//[分形的递归输出](https://pintia.cn/problems/1231458003844222976/PROBLEM_DESCRIPTION)
#pragma warning(disable : 4996)
#include <stdio.h>
#include <assert.h>
#include <iostream> // std::cout, std::cin
#include <fstream>	// fstream::read, ::write, ::getline
#include <string>   // std::string
#include <algorithm>// std::transform
#include <cstring>	// string.h/memory.h => string => cstring::memset, ::memcpy
#include <ctime>	// time.h => ctime::srand(time(NULL)), ::rand(), ::clock()
#include <vector>
#include <queue>
using namespace std;
//#define DEBUG	//提交时注释此行
#ifdef DEBUG
FILE *fi = freopen("1.in","r",stdin);
FILE *fo = freopen("1.out","w",stdout);
#define D(x) x
#else 
#define D(x) 
#endif

//函数调用的运行时间统计（秒）
int array_find(int n, int m);
void Llist_find(int n, int m);
void queue_find(int n, int m);
int iteration_find(int n, int m);
int recursion_find(int n, int m);
//被调用的函数各种各样，这里举例的接口为void func(int n, int m);
double elapse_time(int (*f)(int,int), int n, int m)
{
	clock_t start,end;
	start = clock();
	f(n,m);
	end = clock();
	return (double)(end-start)/CLOCKS_PER_SEC;
}

double elapse_time1(void (*f)(int, int), int n, int m)
{
    clock_t start, end;
    start = clock();
    f(n, m);
    end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main()
{
    int n = 0, m = 0, i = 0;
	double et1, et2, et3, et4, et5;
    FILE* f1 = fopen("in.txt", "r");
    FILE* f2 = fopen("out.txt", "w");
	D(printf("输入若干组n和m: ");)
	while (fscanf(f1,"%d %d\n",&n,&m)) {
		//*/ 
        if (n == 0 || m == 0) {
            break;
        }
		et1 = elapse_time(array_find,n,m);
        et2 = elapse_time1(Llist_find, n, m);
        et3 = elapse_time1(queue_find, n, m);
        et4 = elapse_time(iteration_find, n, m);
        et5 = elapse_time(recursion_find, n, m);
        fprintf(f2, "第%d组结果：\n",++i);
        fprintf(f2, "输入数据：%d %d\n", n,m);
        fprintf(f2, "数组实现: %-.4fs\n", et1);
        fprintf(f2, "链表实现: %-.4fs\n", et2);
        fprintf(f2, "队列实现: %-.4fs\n", et3);
        fprintf(f2, "反向迭代: %-.4fs\n", et4);
        fprintf(f2, "正向递归: %-.4fs\n", et5);
        fprintf(f2, "---------------------\n");
		//*/		
	}

#ifdef DEBUG
	fclose(fi);
	fclose(fo);
#endif
	return 0;
}
/* 请在这里填写答案 */

//josephus_ring(约瑟夫环问题)

//解法一：数组实现

int array_find(int n, int m) {

    int arr[10000] = { 0 };
    int count = 0;
    int i = 0, k = 0;

    while (count != n - 1) {
        i++;
        if (i > n) {
            i = 1;
        }
        if (arr[i] == 0) {
            k++;
            if (k == m) {
                arr[i] = 1;
                count++;
                k = 0;
            }
        }
    }
    for (i = 1; i < n; i++) {
        if (arr[i] == 0) {
            return i;
        }
    }
    return 0;
}

//解法二:链表实现

typedef struct header
{
    int length;
    struct node* next;
}head;
typedef struct node
{
    int val;
    struct node* next;
}node;
head* listcreat()
{
    head* p;
    p = (head*)malloc(sizeof(head));
    p->next = NULL;
    p->length = 0;
    return p;
}
void listinsert(head* p, int pos, int x)
{
    if (p == NULL || pos<0 || pos>p->length)
    {
        printf("listinsert():error\n");
        return;
    }
    node* temp = (node*)malloc(sizeof(node));
    temp->val = x;
    node* pcur = p->next;//指向第一个数据节点
    node* plast = p->next;//指向最后一个数据节点
    while (pcur != NULL && plast->next != pcur)//使plast指向最后一个节点
    {
        plast = plast->next;
    }
    if (p->length == 0)//判断循环链表为空的情况
    {
        p->next = temp;
        temp->next = temp;
    }
    else if (pos == 0)//头插
    {
        plast->next = temp;
        temp->next = pcur;
        p->next = temp;
    }
    else if (pos == p->length)//尾插
    {
        plast->next = temp;
        temp->next = pcur;
    }
    else
    {
        node* pval = p->next;//pval用来指向要插入位置的数据节点
        for (int i = 1; i < pos; i++)
        {
            pval = pval->next;
        }
        temp->next = pval->next;
        pval->next = temp;
    }
    p->length++;
    return;
}
void listdelete(head* p, int x)
{
    node* temp;//temp指向要删除的节点
    temp = p->next;
    for (int i = 0; i < p->length; i++)
    {
        if (temp->val == x)
        {
            break;
        }
        temp = temp->next;
    }
    node* pcur = p->next;//pcur指向第一个节点
    node* plast = p->next;//plast用来指向最后一个节点
    while (plast->next != pcur)
    {
        plast = plast->next;
    }
    if (temp->val != x)
    {
        printf("listprintf():error\n");
        return;
    }
    if (p->length == 1)//只有一个元素时
    {
        p->next = NULL;
    }
    else if (temp == pcur)//删除的是第一个节点
    {
        p->next = pcur->next;
        plast->next = pcur->next;
    }
    else if (temp == plast)//删除的是最后一个节点
    {
        node* pre = p->next;//指向倒数第二个节点
        while (pre->next != plast)
        {
            pre = pre->next;
        }
        pre->next = pcur;
    }
    else
    {
        node* pre = p->next;
        while (pre->next != temp)//使pre指向temp的前一个元素
        {
            pre = pre->next;
        }
        pre->next = temp->next;
    }
    p->length--;
}
void listprint(head* p)
{
    if (p == NULL || p->length == 0)
    {
        printf("listprint():error");
        return;
    }
    node* temp = p->next;
    for (int i = 0; i < p->length; i++)
    {
        //printf("%d ", temp->val);
        temp = temp->next;
    }
    //printf("\n");
    return;
}
void Llist_find(int n, int m)
{
    head* p;
    p = listcreat();
    for (int i = n; i > 0; i--)
    {
        listinsert(p, 0, i);
    }
    //listprint(p);
    node* temp = p->next;
    int count = 1;
    //printf("被踢顺序\n");
    while (temp->next != temp)//剩下一个数时结束循环
    {
        if (count == m)
        {
            node* pre = p->next;
            while (pre->next != temp)//指向temp的前一个节点
            {
                pre = pre->next;
            }
            //printf("%d ", temp->val);
            listdelete(p, temp->val);
            temp = pre;
            count = 0;
            continue;
        }
        count++;
        temp = temp->next;
    }
    //printf("\n");
    //printf("链表中最后被剩下的是：\n");
    listprint(p);
}

//解法三:队列实现

queue<int> res;

void queue_find(int n, int m) {
    for (int i = 1; i <= n; i++)
    {
        res.push(i);
    }
    int cnt = 0;
    while (!res.empty())
    {
        for (int i = 1; i <= m - 1; i++)//执行k-1次
        {
            res.push(res.front());//将队首元素放队尾去
            res.pop();
        }
        //循环结束后输出队首元素
        //cout << res.front() << " ";
        res.pop();//出列
    }
}

//解法四:反向迭代
int iteration_find(int n, int m) {
    int thelast = 0;
    for (int i = 2; i <= n; ++i) {
        thelast = (thelast + m) % i;
    }

    return thelast;
}


//解法五:正向递归
int recursion_find(int n, int m) {
    int thelast = 0;
    if (n == 1) {
        return 0;
    }
    return ((recursion_find(n - 1, m) + m) % n);
}


