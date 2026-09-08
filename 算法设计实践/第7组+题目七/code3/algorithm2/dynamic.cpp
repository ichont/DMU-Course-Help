#include "stdio.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <fstream>

using namespace std;

#define MIN(a,b) (a<b ? a:b)
#define MAXINT  1000000
int N0,K0,A0,B0,C0;
int p[102][102];		//公路状态 
ifstream ifile;         //打开输入数据文件以及要写入的文件
				
void readfile()
{
	ifile>>N0>>K0>>A0>>B0>>C0;
	for (int i=1;i<=N0;i++)          //给每一个位置赋值
	{
	  	for (int j=1;j<=N0;j++)
	  	{
	   		ifile>>p[i][j];
	  	} 
	}	
}		
int dp()
{
	int N=N0,K=K0,A=A0,B=B0,C=C0;
	int f[N+1][N+1][2];		 //三维数组，记录最小费用以及还能行驶的路程,f(x,y,0)、f(x,y,1)
	int i,j,k;
	int s[4][3]={-1,0,0,0,-1,0,1,0,B,0,1,B};   //从x-1到x、y-1到y都是0； 
	for (i=1;i<=N;i++)
	{
	  	for (j=1;j<=N;j++)
	  		f[i][j][0]=MAXINT;             //f（i，j，0）初始化为最大值 
	}
	for (i=1;i<=N;i++)
	  	for (j=1;j<=N;j++)
	   		f[i][j][1]=K;			//f（i，j，1）初始化为K 
	f[1][1][0]=0;
	f[1][1][1]=K;
	
	int x,y;
	bool pd=true;
	while(pd)
	{
	  	pd=false;			//判断是否更新了点，如果有更新则要重新进行一次遍历 
	  	for (x=1;x<=N;x++)           //其实x为内层，y为外层，对应坐标以及s的坐标系
	  	{
	   		for (y=1;y<=N;y++)
	   		{
	    		if (x==1&&y==1)
	     			continue;
	    		int minf0=MAXINT;
	    		int nowf0;
	    		int Prex,Prey;			//变化成（x、y）前的坐标（四个位置可抵达x，y） 
	    		int nowf1;
	    		int minf1;         // 最小f0对应的 f1 
	    		for (k=0;k<4;k++)	//四种移动方式 
	    		{
	     			Prex=x+s[k][0];
	     			Prey=y+s[k][1];
	     			if (Prex<1||Prex>N||Prey<1||Prey>N)   //边界检查！！
	     		 	continue;
	     		 	
	     			nowf0=f[Prex][Prey][0]+s[k][2];
	     			nowf1=f[Prex][Prey][1]-1;			//从（px，py）到（x，y）的f（x，y，0/1） 
	     			
	     			if (p[x][y]==1)        //有加油站
	     			{
	      				nowf0+=A;
	      				nowf1=K;
	     			}
	     			else if ((nowf1==0)&&(x!=N||y!=N)) //没有加油站，并且没有油了
	     			{
	      				nowf0+=A+C;
	      				nowf1=K;
	     			}
	     											//有油又无站 
	     			if (nowf0<minf0||(nowf0==minf0&&nowf1>minf1))       //四种情况中的最小值 
	     			{
	      				minf0=nowf0;
	      				minf1=nowf1;
	     			}
	    		}
	    		if (f[x][y][0]>minf0||(f[x][y][0]==minf0&&f[x][y][1]<minf1))      //如果发现周围有更好的解，则替换f
	    		{
	     			pd=true;				//有更新的点，因此之后要进行一次重新遍历 
	     			f[x][y][0]=minf0;		//也可以直接进行从头开始，但速度会变慢 
	     			f[x][y][1]=minf1;
	    		}
	   		}
	  	}
	}  
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			cout<<f[i][j][0]<<"    ";
		}
		cout<<endl;
	}
	return f[N][N][0];
} 
		  
int main()
{

	int ans;
	ifile.open("./input.txt");
	readfile(); 
	ifile.close();
   
	ans=dp();     //动归过程 

	ofstream ofile("./output.txt");
	ofile<<ans;
	ofile.close();
}
