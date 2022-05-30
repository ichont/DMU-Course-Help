#include<stdio.h>
#include<string.h>
struct student
{
char name[20];//名字
int number;//学号
int gaoshu;//数学成绩
int yingyu;//英语成绩
int sum;//总成绩
float math;
float English;
 
}
stu[60];

int n;//学生数量

void menu()//菜单
{
printf("\n");
printf("***********************************\n");
printf("******   学生成绩管理系统   ******\n");
printf("******   按1 输入学生信息   ******\n");
printf("******   按2 输出学生信息   ******\n");
printf("******   按3 查询学生信息   ******\n");
printf("******   按4 修改学生信息   ******\n");
printf("******   按5 删除学生信息   ******\n");
printf("******   按6 插入学生信息   ******\n");
printf("******   按7 排序成绩信息   ******\n");
printf("******   按11  数学平均分   ******\n");
printf("******   按12  英语平均分   ******\n");
printf("******   按0 退出系统       ******\n");
printf("***********************************\n");
}
void input()//学生信息的录入
{
	int i,j=1;
	printf("\n  请输入总学生数量:");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		printf(" 输入第%d个学生相关信息\n",j++);
		printf("输入姓名\n");
		scanf("%s",stu[i].name);
		getchar();
		
		printf("输入学号\n");
		scanf("%d",&stu[i].number);
		printf("输入数学成绩\n");
		scanf("%d",&stu[i].gaoshu);
		printf("输入英语成绩\n");
		scanf("%d",&stu[i].yingyu);
		stu[i].sum=stu[i].gaoshu+stu[i].yingyu;
		printf("该学生的总成绩:%d\n",stu[i].sum);
	}
}


void output()//学生信息输出
{
	int i;
	printf("----------学生信息的是----------\n");
	if(n==0)
		printf(" ++++++这里没有信息++++++\n");
	else 
		printf("名字       学号       数学成绩   英语成绩   总分   \n");
		for(i=1;i<=n;i++)
		{
			printf("%-11s",stu[i].name);
			printf("%-11d",stu[i].number);
			printf("%-11d",stu[i].gaoshu);
			printf("%-11d",stu[i].yingyu);
			stu[i].sum=stu[i].gaoshu+stu[i].yingyu;
			printf("%-6d\n",stu[i].sum);
		}
 
}

void search()//学生信息查询
{
	int num,i,t;
	char a[20],k;
	if(n!=0)
	{
		printf("选择查找条件(1:学号 2:名字)\n");
		scanf("%d",&t);
		if(t==1)
		{
			printf("输入您要查找的学生的学号\n");
			scanf("%d",&num);
			for(i=1;i<=n;i++)
			{
				if(stu[i].number==num)
				{
					printf("名字：%s",stu[i].name);
					printf("学号：%d",stu[i].number);
					printf("数学成绩：%d\n",stu[i].gaoshu);
					printf("英语成绩：%d\n",stu[i].yingyu);
					stu[i].sum=stu[i].gaoshu+stu[i].yingyu;
					printf("该学生的总成绩:%d\n",stu[i].sum);
					break;
				}
			}
			if(i>n) 
				printf("您查找的信息不存在或者学号输入错误\n");
		}
		if(t==2)
		{
			printf("输入您要查找的学生的名字\n");
			scanf("%s",a);
			for(i=1;i<=n;i++)
			{
				k=strcmp(stu[i].name,a);
				if(k==0)
				{
					printf("名字：%s",stu[i].name);
					printf("学号：%d",stu[i].number);
					printf("数学成绩：%d\n",stu[i].gaoshu);
					printf("英语成绩：%d\n",stu[i].yingyu);
					stu[i].sum=stu[i].gaoshu+stu[i].yingyu;
					printf("该学生的总成绩:%d\n",stu[i].sum);
					break;
 
				}
			}
			if(i>n) printf("您查找的信息不存在或者学号输入错误\n");
		}
 
	}
	else 	
		printf("对不起，这里没有学生信息\n");
}

void change()//学生信息修改
{
	int num,i;
	printf("输入您要修改的学生的学号\n");
	scanf("%d",&num);
	if(n==0)//如果没有学生信息录入
		printf(" ++++++这里没有信息++++++\n");
	else
	{
		for(i=1;i<=n;i++)
		{
			if(stu[i].number==num)//如果学号匹配
			{
				printf("您要修改的学生信息为\n");
				printf("名字：%s",stu[i].name);
				printf("学号：%d",stu[i].number);
				printf("数学成绩：%d\n",stu[i].gaoshu);
				printf("英语成绩：%d\n",stu[i].yingyu);
				stu[i].sum=stu[i].gaoshu+stu[i].yingyu;
				printf("该学生的总成绩:%d\n",stu[i].sum);
				printf("\n");
				break;
 
			}
			
  
		}
		
 
		if(i>n) //没有匹配的学号
			printf("您查找的信息不存在或者学号输入错误\n");
		else//有匹配的学号
		{
			printf("输入姓名\n");
			scanf("%s",stu[i].name);
			getchar();
			printf("输入学号\n");
			scanf("%d",&stu[i].number);
			printf("输入数学成绩\n");
			scanf("%d",&stu[i].gaoshu);
			printf("输入英语成绩\n");
			scanf("%d",&stu[i].yingyu);
		}
	}
}

void del()//学生信息删除
{
	int i,j,e,num;
	if(n!=0)//学生信息不为空
	{
		printf(" ****这是所有学生的信息****\n");
		for(i=1;i<=n;i++)//打印所有学生信息
		{
		printf("--------------------------*\n");
		printf("名字：%s\n",stu[i].name);
		printf("    *\n");
		printf("学号：%d\n",stu[i].number);
		printf("    *\n");
		printf("数学成绩：%d\n",stu[i].gaoshu);
		printf("英语成绩：%d\n",stu[i].yingyu);
		stu[i].sum=stu[i].gaoshu+stu[i].yingyu;
		printf("该学生的总成绩:%d\n",stu[i].sum);
		printf("--------------------------*\n");
		}
		printf("请输入您要删除的学生的学号:");
		scanf("%d",&num);
		for(i=1;i<=n;i++)
		{
			if(stu[i].number==num)
			{
				j=i;
				for(e=i-1;e<n;e++,j++)
				{
					strcpy(stu[j].name,stu[j+1].name);
					stu[j].number=stu[j+1].number;
					stu[j].gaoshu=stu[j+1].gaoshu;
					stu[j].yingyu=stu[j+1].yingyu;
					n--;
				}
			}	
		}	
		printf("**********该学生信息已删除**********\n");
 
	}
	else
		printf("对不起，这里没有学生信息\n");
}


void add()//学生信息插入
{
	int i,j,t;
	if(n!=0)
	{
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printf("^ 注: 下面已有信息，如有重复请不要插入 ^\n");
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printf("\n");
		for(i=1;i<=n;i++)
		{
  
			printf("名字：%s",stu[i].name);
			printf("学号：%d",stu[i].number);
			printf("数学成绩：%d\n",stu[i].gaoshu);
			printf("英语成绩：%d\n",stu[i].yingyu);
			stu[i].sum=stu[i].gaoshu+stu[i].yingyu;
			printf("该学生的总成绩:%d\n",stu[i].sum);
			printf("\n");
		}
		printf("是否继续插入(是：y 否：n)\n");
		printf("%c您的选择是:",t=getchar());
		t=getchar();
		if(t=='y')
		{
			j=n;
			printf("**********请插入学生相关信息**********\n");
			printf("输入姓名\n");
			scanf("%s",stu[j+1].name);
			getchar();
			printf("输入学号\n");
			scanf("%d",&stu[j+1].number);
			printf("输入数学成绩\n");
			scanf("%d",&stu[j+1].gaoshu);
			printf("输入英语成绩\n");
			scanf("%d",&stu[j+1].yingyu);
			strcpy(stu[j+2].name,stu[j+1].name);
			stu[j+2].number=stu[j+1].number;
			stu[j+2].gaoshu=stu[j+1].gaoshu;
			stu[j+2].yingyu=stu[j+1].yingyu;
			printf("  该学生信息已经插入\n");
			n++;
		}	
		else
			printf("\n (▔▽▔)插入程序结束，请重新选择");printf("\n");
  
	}
	else
	{
		i=1;printf("请输入要插入学生的相关信息\n");
		printf("输入姓名\n");
		scanf("%s",stu[i].name);
		getchar();
		printf("输入学号\n");
		scanf("%d",&stu[i].number);
		printf("输入高数成绩\n");
		scanf("%d",&stu[i].gaoshu);
		printf("输入英语成绩\n");
		scanf("%d",&stu[i].yingyu);
		n++;
  
	}
  
}


void paixu()//按总分成绩排序
{
	int i,j,t;
	if(n!=0)
	{
		printf("该排序是按照总分成绩从高到低进行排序\n");
		for(i=1;i<=n;i++)
			for(j=1;j<n;j++)
			{ 
				if(stu[j].sum<stu[j+1].sum)
				{
					t=stu[j].sum;//交换成绩顺序
					stu[j].sum=stu[j+1].sum;
					stu[j+1].sum=t;
				}
			}
			for(i=1;i<=n;i++)//显示排序后结果
			{
				printf("名字：%s\n",stu[i].name);
				printf("学号：%d\n",stu[i].number);
				printf("数学成绩：%d\n",stu[i].gaoshu); 
				printf("英语成绩：%d\n",stu[i].yingyu);
				printf("总成绩：%d\n",stu[i].sum);
			}
  
	}
	else
		printf(" ++++++这里没有信息++++++\n");
}

void math()
{
	int i;
	stu[i].math=0;
	float mathsum=0;
	for(i=0;i<=n;i++)
	{
		mathsum=stu[i].gaoshu+mathsum;
	}
	stu[i].math=mathsum/n;
	printf("数学平均分是:%f\n",stu[i].math);
	
}

void English()
{
	int i;
	stu[i].English=0;
	float Englishsum=0;
	for(i=0;i<=n;i++)
	{
		Englishsum=stu[i].yingyu+Englishsum;
	}
	stu[i].English=Englishsum/n;
	printf("英语平均分是:%f\n",stu[i].yingyu);
	
}


int main()
{
	int a,b=1;
	while(b)
	{
		menu();//功能菜单
		printf("您选择的是: ");
		scanf("%d",&a);
		printf("\n");
		switch(a)//功能选择
		{
			case 1:input();
			break;//输入
			case 2:output();
			break;//输出
			case 3:search();
			break;//查找
			case 4:change();
			break;//修改
			case 5:del();
			break;//删除
			case 6:add();
			break;//插入
			case 7:paixu();
			break;//排序
			case 11:math();
			break;
			case 12:English();
			break;
			case 0:b=0;
			break;//退出
		}
	}
	printf("学生管理系统已退出( ^_^ )\n");
	
	return 0;
}