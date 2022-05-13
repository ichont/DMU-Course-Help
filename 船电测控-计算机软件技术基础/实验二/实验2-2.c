#include<stdio.h>
void Bubblesort(int a[])
{
	int x,y;
	int t;
	for(y=0;y<10;y++)
	{
		for(x=0;x<9;x++)
		{
			if(a[x]>a[x+1])
			{
				t=a[x];
				a[x]=a[x+1];
				a[x+1]=t;
			}
		}
	}
}
int main(void)
{
	int a[] = {45,92,18,30,25,67,22,51,83,16};
	int x;
	int b=1;
	printf("排序后的数组是：\n");
	Bubblesort(a);
	for(x=0;x<=9;x++)
	{
		printf("%d ",a[x]);
	}
	printf("\n");
	int key;  //存放要查找的数
	int low = 0;
	int high = sizeof(a)/sizeof(a[0]) - 1;
	int mid;
	int flag = 0;  //标志位, 用于判断是否存在要找的数
	
	while(b==1)
	{
		printf("请输入您想查找的数:");
		scanf("%d", &key);
		flag=0;
		low=0;
		high = sizeof(a)/sizeof(a[0]) - 1;
		while ((low <= high))
		{
			mid = (low + high) / 2;
			if (key < a[mid])
			{
				high = mid - 1;
			}
			else if (a[mid] < key)
			{
				low = mid +1;
			}
			else
			{
				printf("要查找的数字在数组中第%d位\n", mid+1);
				flag = 1;
				break;
			}
		}
		if (0 == flag)
		{
			printf("对不起，没有找到相关数据\n");
		}
		printf("输入1继续输入，0退出:");
		scanf("%d",&b);
	}
	return 0;
}