#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
int map[102][102],f[102][102][11],n,k,a,b,c,an=199999999;
void dfs(int x,int y,int fy,int rs)//横坐标，纵坐标，目前费用，剩余步数 
{
	int add=0;//此步费用 
	if (map[x][y]==-1) return;//边界 
	if (rs<=0||fy>=an) return;//最优性剪枝 
	rs--;
	for (int i=rs;i<=k;i++)//一个剪枝操作：当此坐标剩i（rs（当前剩步）<=i<=k）步时，
	if (f[x][y][i]<=fy) return;//费用还比目前费用少，则可剪枝。
	f[x][y][rs]=fy;//更新此坐标剩rs步时最小费用（记忆化） 
	if (x==n&&y==n)
	{
		an=min(an,fy);//更新答案 
		return;
	}
	if (map[x][y]==1) add=a,rs=k;//强制加油 
	if (rs==0) add=a+c,rs=k;//没油了，才设站加油 
	dfs(x+1,y,fy+add,rs);
	dfs(x,y+1,fy+add,rs);
	dfs(x-1,y,fy+add+b,rs);
	dfs(x,y-1,fy+add+b,rs);//扩展 
}
int main()
{
	scanf("%d%d%d%d%d",&n,&k,&a,&b,&c);
	for (int i=0;i<=n+1;i++)
	map[0][i]=map[i][0]=map[i][n+1]=map[n+1][i]=-1;//设边界 
	for (int i=1;i<=n;i++)
	for (int j=1;j<=n;j++)
	{
		scanf("%d",&map[i][j]);
		for (int k=0;k<=10;k++)
		f[i][j][k]=99999999;//初始化 
	}
	dfs(1,1,0,k+1);
	printf("%d",an);
	return 0;//好习惯 
}
