#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int length, width, i, j, **mat, **sig;			//mat存储棋盘信息，sig存储路径信息
int dx[4] = { 0,0,-1,1 }, dy[4] = { -1,1,0,0 };	//dx dy表示上下左右移动时坐标的变化
int x2, y2;			//终点坐标
bool flag = false;	//是否能相连

//判断位置是否合法
bool legal(int x, int y) {
	return (x >= 0 && x < width&&y >= 0 && y < length);
}

//搜索函数
//x y表示位置 dir表示方向 cnt表示拐弯次数
void dfs(int x, int y, int dir, int cnt) {	
	if (x == x2&&y == y2) {		//到达终点
		cout << "TRUE\n";
		flag = true;
		return;
	}
	if (mat[x][y] != 0 || sig[x][y] == 1)	//位置非空或已经搜索过
		return;

	if (cnt == 2) {		//拐弯两次，只能向dir方向搜索
		if (legal(x + dx[dir], y + dy[dir])) {
			sig[x][y] = 1;
			dfs(x + dx[dir], y + dy[dir], dir, cnt);
			sig[x][y] = 0;
		}
	}
	
	if (cnt < 2) {		//拐弯不到两次，可向四个方向搜索
		for (int i = 0; i < 4; ++i) {
			if (legal(x + dx[i], y + dy[i])) {
				if (dir == i) {
					sig[x][y] = 1;
					dfs(x + dx[i], y + dy[i], dir, cnt);
					sig[x][y] = 0;
				}
				else {
					sig[x][y] = 1;
					dfs(x + dx[i], y + dy[i], i, cnt + 1);
					sig[x][y] = 0;
				}
			}
		}
	}
}

//对起点的搜索
void trigger(int x, int y) {
	for (int i = 0; i < 4; ++i) {
		if (legal(x + dx[i], y + dy[i])) {
			sig[x][y] = 1;
			dfs(x + dx[i], y + dy[i], i, 0);
			sig[x][y] = 0;
			if (flag) break;
		}
	}
	if (!flag) {	//flag为false表示不能相连
		cout << "FALSE\n";
	}
}

int main()
{
	ifstream in("in.dat");
	int x1, y1;

	in >> width >> length;

	mat = new int*[width];
	sig = new int*[width];
	for (i = 0; i < width; ++i) {
		mat[i] = new int[length];
		sig[i] = new int[length];
	}

	for (i = 0; i < width; ++i)
		for (j = 0; j < length; ++j) {
			in >> mat[i][j];
			sig[i][j] = 0;
		}

	for (i = 0; i < width; ++i) {
		for (j = 0; j < length; ++j)
			cout << mat[i][j] << ' ';
		cout << '\n';
	}

	in >> x1 >> y1 >> x2 >> y2;

	cout << '(' << x1 << ',' << y1 << ")  " << '(' << x2 << ',' << y2 << ")\n";

	x1--;
	y1--;
	x2--;
	y2--;
	if (mat[x1][y1] != mat[x2][y2]) {	//若两坐标图案不同则显然不能相连
		cout << "FALSE\n";
	}
	else {
		trigger(x1, y1);	//两坐标图案相同可以开始搜索
	}

	for (i = 0; i < width; ++i) {
		delete[]mat[i];
		delete[]sig[i];
	}
	delete mat;
	delete sig;

    return 0;
}

