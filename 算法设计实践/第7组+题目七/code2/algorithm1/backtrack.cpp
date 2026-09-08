#include<iostream>
#include<string>
using namespace std;
string num[10];
//判断是否能填入n 
bool check(int x,int y,int n) {
	for (int i = 0; i < 9; i++) {
		if (num[x][i] - '0' == n)return false;// 判断行是否存在重复
		if (num[i][y] - '0' == n)return false;// 判断列是否存在重复
	}
	//开始判断同色九宫格
	int a = x / 3 * 3;
	int b = a + 3;
	int c = y / 3 * 3;
	int d = c + 3;
	for (int i = a; i < b; i++) {
		for (int j = c; j < d; j++) {
			if (num[i][j] - '0' == n)return false;
		}
	}
	return true;
}

void DFS(int x,int y) {
	
	if (x>8) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << num[i][j];
			}
			cout << endl;
		}
		return;
	}  //填充完毕 
	
	if (num[x][y] != '0') {
		DFS(x+(y+1)/9,(y+1)%9);
		
	} //已有预设数字跳过该处，否则尝试填充 1~9
	else {
		for (int i = 1; i <= 9; i++) {
			if (check(x, y, i)) {
				num[x][y] = i + '0';
				DFS(x + (y + 1) / 9, (y + 1) % 9);
				num[x][y] = '0';
			}
		}
	}
}
int main() {
	for (int i = 0; i < 9; i++) {
		cin >> num[i];
	}
	DFS(0, 0);
	return 0;
}

