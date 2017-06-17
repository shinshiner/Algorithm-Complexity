// lianliankan.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int length, width, i, j, **mat, **sig;			//mat�洢������Ϣ��sig�洢·����Ϣ
int dx[4] = { 0,0,-1,1 }, dy[4] = { -1,1,0,0 };	//dx dy��ʾ���������ƶ�ʱ����ı仯
int x2, y2;			//�յ�����
bool flag = false;	//�Ƿ�������

//�ж�λ���Ƿ�Ϸ�
bool legal(int x, int y) {
	return (x >= 0 && x < width&&y >= 0 && y < length);
}

//��������
//x y��ʾλ�� dir��ʾ���� cnt��ʾ�������
void dfs(int x, int y, int dir, int cnt) {	
	if (x == x2&&y == y2) {		//�����յ�
		cout << "TRUE\n";
		flag = true;
		return;
	}
	if (mat[x][y] != 0 || sig[x][y] == 1)	//λ�÷ǿջ��Ѿ�������
		return;

	if (cnt == 2) {		//�������Σ�ֻ����dir��������
		if (legal(x + dx[dir], y + dy[dir])) {
			sig[x][y] = 1;
			dfs(x + dx[dir], y + dy[dir], dir, cnt);
			sig[x][y] = 0;
		}
	}
	
	if (cnt < 2) {		//���䲻�����Σ������ĸ���������
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

//����������
void trigger(int x, int y) {
	for (int i = 0; i < 4; ++i) {
		if (legal(x + dx[i], y + dy[i])) {
			sig[x][y] = 1;
			dfs(x + dx[i], y + dy[i], i, 0);
			sig[x][y] = 0;
			if (flag) break;
		}
	}
	if (!flag) {	//flagΪfalse��ʾ��������
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
	if (mat[x1][y1] != mat[x2][y2]) {	//��������ͼ����ͬ����Ȼ��������
		cout << "FALSE\n";
	}
	else {
		trigger(x1, y1);	//������ͼ����ͬ���Կ�ʼ����
	}

	for (i = 0; i < width; ++i) {
		delete[]mat[i];
		delete[]sig[i];
	}
	delete mat;
	delete sig;

    return 0;
}

