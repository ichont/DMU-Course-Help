#include<stdio.h>
#define MAXNUM 20
#define true 1
#define false 0
typedef struct 

	{  
		int data[MAXNUM];
		int length;
	}list_type;
	/* 提示：创建顺序表函数 */
	/*create a list:input data from keyboard,end by -1*/
	void createlist(list_type *lp)
	{
	int i, elem;
	lp->length=0;
	printf("\nplease input datas of the list\n");
	for(i=0; i< MAXNUM; i++)
	{
		scanf(" %d", &elem);
		if(elem== -1) break;
        lp->data[i]=elem;
        lp->length++;
	}
	}
	/* 提示：遍历元素并依次输出函数 */
	void showlist(list_type *lp)
	{
	int i;
	printf("\nThese %d records are:\n", lp->length);
	if(lp->length<=0)
	{
		printf("No data!\n");
		return;
	}
	for(i=0; i<lp->length; i++)
      printf(" %d ", lp->data[i]);
	printf("\nlength of the list is:%d", lp->length);
	}
	void  Insert(list_type *L, int x, int i)
	{ int j; 
	if(L->length>=MAXNUM-1)
	printf("overflow");      //如果表满了，则输出上溢异常
	else if ((i<1)||(i>L->length+1))
		printf("position is not correct!");  //元素的插入位置不合理 
			else { for(j=L->length;j>=i;j--)
                       L->data[j+1]=L->data[j];            //元素后移
                    L->data[i]=x;        //插入元素
                    L->length++;       //表长度增加1
                  }
	}
	void Delete(list_type *L,int i)
	{		int j; if((i<1)||(i>L->length))
	printf(" position is not correct!");
			else { for(j=i+1;j<=L->length;j++) 
						L->data[j-1]=L->data[j];        //元素前移
					L->length--;                      //表长度减1
                 }
		}
int main(void)
{
	list_type l;
	createlist(&l);
	showlist(&l);
	
	return 0;
	
		
}