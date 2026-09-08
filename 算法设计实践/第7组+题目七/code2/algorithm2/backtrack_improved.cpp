#include <iostream>
#include <cstdio>
using namespace std;
int row[9],col[9],grid[9];//000000000~111111111	可行性数组 1表示可以填 
//2^9=32*16=512		2^8+5=256+5=261
int cnt[512],num[261];
int rec[9][9];
inline int g(int x,int y){// 二维坐标 (x, y) 映射到数独游戏中对应的 3x3 小九宫格的索引。
	return ((x/3)*3)+(y/3);
}
//状态更新 （x,y）位置填入z，则（x，y）所处的行，列，九宫格不可填入z 
void flip(int x,int y,int z){ 
	row[x]^=1<<z;//它通过异或运算 (^=) 来翻转指定位置的状态。逐位比较两个数的二进制表示，相同位为0，不同位为1。
	              //具体效果：如果 row[x] 的第 z 位原来是 0，异或后变成 1。                                            
	col[y]^=1<<z;
	grid[g(x,y)]^=1<<z;
}

bool dfs(int now){//有now个数要填入 
	if(!now)	return true;//如果now为0，表示数独已填完，返回true。
	int temp=10,x,y;
	 //找到可填数字最少的位置（x，y），以减少搜索空间。 
	for(int i=0;i<9;++i){        
		for(int j=0;j<9;++j){
			if(rec[i][j])	continue;
			int val=row[i]&col[j]&grid[g(i,j)];  //通过位操作 & ，计算出 (i, j) 位置上可以填的数字集合 val。如：val 的二进制表示 0011，表示该位置可以填 1 和 2
			                                     //val 的每一位表示相应的数字是否可以填，                                 
			if(!val)	return false;//1个也不能填，回溯
			if(temp>cnt[val]){// cnt[val]记录当前位置上可以填的数字个数。取当前位置可以填的最少的数的个数，并记录下这个位置
				temp=cnt[val];
				x=i;y=j;
			}
		}
	}
	//核心部分：通过递归地尝试在最优位置填入可能的数字，并在填入失败时进行回溯。
	int val=row[x]&col[y]&grid[g(x,y)];
	//取出（x，y）中每个课填入的数字 
	for(;val;val-=val&(-val)){ //设计循环，直到 val 为 0中止。每次循环中，val & (-val) 提取出 val 中的最低位的 1，并将 val 中最低位的 1 清零。
	                           // 如果 val 是 011，那么 val & (-val) 会得到 001 。val则变为010 
		int z=num[val&(-val)]; //将二进制数的最低位 1 转换为对应的数字。                                      
		rec[x][y]=z+1;        // 设置数独 (x, y) 位置的值为 z + 1。注意这里 z 是从 0 开始的，所以需要加 1。
		flip(x,y,z);
		if(dfs(now-1))	return true;//递归调用 dfs 函数，尝试填下一个数字。如果成功，直接返回 true
		rec[x][y]=0;                //重置数独网格 (x, y) 位置的值为 0。
		flip(x,y,z);                //回溯时恢复状态，再次调用 flip ，对应的行，列，九宫格中，将 z 号数字的可填状态翻转回原状态。
	}
	return false;//无解，返回上一层 
}
int main(){
	//预先处理 
	for(int i=0;i<(1<<9);++i){
		//预先计算二进制数i中含有1的个数 即可以填的数字个数，有助于快速选择当前最优的填数位置，从而优化搜索过程。
		//cnt[100010001(二进制数)] = 3
		for(int j=i;j;j-=j&(-j)){//每次将 j 的最低位的 1 置零。
			++cnt[i];
		}
	}
	for(int i=0;i<9;++i){//快速计算最低位1的位置，可填数字的二进制表示到实际的数字值的映射，便于后续的状态更新和操作。
		num[1<<i]=i;
	}
	//初始化 
	for(int i=0;i<9;++i){
		//初始化行，列，九宫格标记数组                                                                      （3） 
		//左移运算符 << 将 1 左移9位，结果是 1000000000（二进制），相当于十进制的 512。
		//在二进制中，511 表示为 111111111，即9位全为1,表示可填任意数字 
		row[i]=col[i]=grid[i]=(1<<9)-1;
	}
	for(int i=0;i<9;++i){
		for(int j=0;j<9;++j){
			scanf("%d",&rec[i][j]);
		}
	}
	//初始化计数器 ，计算一共需要填充多少个数 
	int tot=0;
	for(int i=0;i<9;++i){
		for(int j=0;j<9;++j){
			if(rec[i][j]) flip(i,j,rec[i][j]-1);//如果rec[i][j]是0，进行标记	
			else	++tot;//如果rec[i][j]是0，表示该位置还没有填数 ，计数器+1 
		}
	}
	dfs(tot);
	for(int i=0;i<9;++i){
		for(int j=0;j<9;++j){
			printf("%d ",rec[i][j]);
		}
		printf("\n");
	}
	return 0;
}
