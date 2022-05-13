#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>
#define true 1
#define false 0
//    定义链表中的节点  
typedef struct node  
{  
    int member;                //    节点中的成员  
    struct node *pNext;        //    指向下一个节点的指针  
}Node,*pNode;  
  
//    函数声明  
pNode CreateList();                 //  创建链表函数  
void TraverseList(pNode );            //  遍历链表函数  
bool Insert_Node(pNode ,int ,int);    //    链表节点插入函数,第一个参数是头节点，第二个参数是要在第几个节点前插入，第三个参数是要插入的数据  
int Del_Node(pNode,int );        //    删除链表节点,第一个参数是头节点，第二个参数是删除第几个节点，第三个作为  
int main()  
{  
    pNode pHead = NULL;                //  定义初始化头节点，等价于 struct Node *pHead == NULL  
    int data;                        // 作为Insert_Node函数的第三个参数  
    int num;                        //    作为Inset_Node函数第二个参数  
    int choose;      
    int return_val;  
    pHead = CreateList();            //  创建一个非循环单链表，并将该链表的头结点的地址付给pHead  
    printf("你输入的数据是：");  
    TraverseList(pHead);    //  调用遍历链表函数  
    printf("是否还要进行如下操作：\n");  
    printf("1.插入数据      2.退出\n");  
    printf("请输入：");  
    scanf("%d",&choose);  
	while(choose==1)
	{
    switch (choose)  
    {  
        case 1:  
            {  
                printf("请输入要在第几个节点前插入数据：");  
                scanf("%d",&num);  
                printf("请输入要插入的数据：");  
                scanf("%d",&data);  
                if(Insert_Node(pHead,num,data) == true)  
                {  
                    printf("插入成功\n插入后的数据是：\n");  
                    TraverseList(pHead);  
                }  
                else  
                {  
                    printf("插入失败\n");  
                }  
                printf("操作完成后的数据是：");  
                TraverseList(pHead);  
                break;  
            }  
        case 2:  
            {  
                break; 
            }  
    } 
	printf("是否还要进行如下操作：\n");  
    printf("1.插入数据      2.退出\n");  
    printf("请输入：");  
    scanf("%d",&choose);
	}	
    return 0;  
}  
  
//    创建链表函数  
pNode CreateList()  
{  
    int i;                                            //    用于下面循环  
    int len;                                        //    用来存放有效节点的字数  
    int val;                                        //    用于临时存放用户输入的数据  
    pNode pHead = (pNode)malloc(sizeof(Node));        //  分配一个不存放有效数据的头结点  
    pNode pTail = pHead;                            //    链表的最后一个节点  
    pTail->pNext = NULL;                            //    最后一个节点的指针置为空  
    printf("请输入节点个数：");  
    scanf("%d",&len);  
    for(i = 0; i < len; i++)  
    {  
        printf("第 %d 个节点的数值（输入后按enter键输入下一个）：",i+1);  
        scanf("%d",&val);  
        pNode pNew = (pNode)malloc(sizeof(Node));    //    为节点分配空间  
        pNew->member = val;                            //将用户输入的数据赋给节点的成员  
        pTail->pNext = pNew;                        //将最后一个节点的指针指向下一个新的节点  
        pNew->pNext = NULL;                            //将新节点中的指针置为空  
        pTail = pNew;                                //将新节点赋给最后的一个节点  
    }  
    return pHead;                                    //返回头节点  
  
}  
  
//    遍历链表函数  
void TraverseList(pNode pHead)  
{  
    pNode p = pHead->pNext;                            //将头节点的指针给予临时节点p  
    while(NULL != p)                                //节点p不为空，循环      
    {  
        printf("%d ",p->member);                      
        p = p->pNext;                                  
    }  
    printf("\n");  
    return ;  
}  
  
//    链表节点插入函数  
//    第一个参数是头节点，第二个参数是要在第几个节点前插入，第三个参数是要插入的数据  
bool Insert_Node(pNode pHead, int front,int data)  
{  
    int i = 0;  
    pNode _node = pHead;  
    pNode pSwap;                                //    用于交换  
    if ((front < 1) && (NULL != _node))        //判断用户输入的数据是否大于等于1,及_node是否为空  
    {  
        return false;  
    }  
    while (i < front - 1)                    //通过循环使指针指向要插入哪个节点前的节点。说的自己都不懂了，还是看下面的图吧。      
    {  
        _node = _node->pNext;  
        ++i;  
    }  
    pNode pNew = (pNode)malloc(sizeof(Node));  
  
    pNew->member = data;                        //    把输入的数据赋给要插入的节点  
    pSwap = _node->pNext;                        //    把下一个节点的地址，给用于交换的pSwap  
    _node->pNext = pNew;                        //    把要插入的节点的地址，给上个节点的指针域  
    pNew->pNext = pSwap;                        //    把插入节点的下一个节点的地址，给插入节点的指针域  
    return true;  
  
}  
  
