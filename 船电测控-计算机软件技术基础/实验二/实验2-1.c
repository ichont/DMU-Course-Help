#include<stdio.h>
int main(void)
{
	int a[] = {45,92,18,30,25,67,22,51,83,16};
	int n;  //存放数组a中元素的个数
	int m;  //查找的数字
	int i;  //循环变量
	int x;
	int t=1;
	int b=1;
	n = sizeof(a) / sizeof(int);  //求出数组中所有元素的个数
	printf("数组中的元素有：");
	for(x=0;x<=9;x++)
	{
		printf("%d ",a[x]);
	}
	printf("\n");
	
	while(b==1)
	{
		t=1;
		printf("请输入要查找的数字:");
		scanf("%d", &m);
		while(t==1)
		{
			for (i=0; i<n; ++i)
			{
				if (a[i] == m)
				{
					printf("要查找的数字在数组中第%d位\n", i+1);
					t=0;
					break;
				}
			}
			if (i == n)
			{
				printf("要查找的数字不存在，请重新输入\n");
				scanf("%d",&m);
			}
			
		}
		printf("输入1继续输入，0退出");
		scanf("%d",&b);
	}
	return 0;
}

