// lkx.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

//将一个建筑拆分为两个unit，一个轮廓由多个unit组成
struct unit
{
	int x, h;
};

unit *p;
ofstream out("out.dat");
int n;

//删去在同一高度的unit，即题中的“消除隐藏线”，输出最后的结果
void print(unit *p) {
	int i = 1;

	out << p[0].x << ' ' << p[0].h << ' ';
	while (i < 2 * n) {
		if (p[i].h == p[i - 1].h) {
			i++;
		}
		else {
			out << p[i].x << ' ' << p[i].h << ' ';
			i++;
		}
	}
}

//将两个轮廓合并成一个
void merge(int lh, int rh) {
	int mid = (lh + rh) / 2, i = lh, j = mid + 1, k = 0;
	unit tmp[100];

	while (i <= mid&&j <= rh) {
		
		if (p[i].x < p[j].x) {
			//找到第一个左部和右部的交叉点
			while (i < mid&&p[i].x < p[j].x&&p[i + 1].x<p[j].x) {
				tmp[k++] = p[i++];
			}
			if (p[i].h < p[j].h) {
				if (i != mid) {
					tmp[k++] = p[i++];
				}
				//左部的最后一个点，可能要把轮廓最后一个unit的高度0提高
				else {
					if (j != mid + 1) {
						tmp[k] = p[i++];
						tmp[k++].h = p[j - 1].h;
					}
					else {
						tmp[k++] = p[i++];
					}
				}
			}
			else {
				//不是左部的最后一个点
				if (i != mid) {
					tmp[k++] = p[i];
					tmp[k] = p[j++];
					tmp[k++].h = p[i++].h;
				}
				else {
					tmp[k] = p[i++];
					tmp[k++].h = p[j - 1].h;
					tmp[k++] = p[j++];
				}
			}
		}
		//对右部的操作和对左部的操作相反
		else {
			while (j < rh&&p[j].x < p[i].x&&p[j + 1].x<p[i].x) {
				tmp[k++] = p[j++];
			}
			if (p[j].h < p[i].h) {
				if (j != rh) {
					tmp[k++] = p[j++];
				}
				else {
					if (j != lh) {
						tmp[k] = p[j++];
						tmp[k++].h = p[i - 1].h;
					}
					else {
						tmp[k++] = p[j++];
					}
				}
			}
			else {
				if (j != rh) {
					tmp[k++] = p[j];
					tmp[k] = p[i++];
					tmp[k++].h = p[j++].h;
				}
				else {
					tmp[k] = p[j++];
					tmp[k++].h = p[i-1].h;
					tmp[k++] = p[i++];
				}
			}
		}
	}

	//合并左右部剩余的部分
	while (i <= mid) {
		tmp[k++] = p[i++];
	}
	while (j <= rh) {
		tmp[k++] = p[j++];
	}

	//将合并结果写回原数组
	for (i = 0; i <= rh - lh; ++i) {
		p[lh + i] = tmp[i];
	}
}

//分割unit数组求解
void divide(int lh, int rh) {
	if (rh - lh <= 2) return;	//区间长度为2时不需要继续分割

	divide(lh, (lh + rh) / 2);	//处理左部
	divide((lh + rh) / 2 + 1, rh);	//处理右部
	merge(lh, rh);				//合并左部和右部
}

int main()
{
	ifstream in("in.dat");
	in >> n;
	p = new unit[2 * n];
	//读入每个建筑的轮廓
	for (int i = 0; i < 2 * n; i += 2) {
		in >> p[i].x >> p[i].h >> p[i + 1].x;
		p[i + 1].h = 0;		//每个建筑的右边高度固定为0
	}

	divide(0, 2 * n - 1);	//求解合并结果
	print(p);				//输出结果

	delete[]p;
	return 0;
}