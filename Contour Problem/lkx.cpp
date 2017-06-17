// lkx.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

//��һ���������Ϊ����unit��һ�������ɶ��unit���
struct unit
{
	int x, h;
};

unit *p;
ofstream out("out.dat");
int n;

//ɾȥ��ͬһ�߶ȵ�unit�������еġ����������ߡ���������Ľ��
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

//�����������ϲ���һ��
void merge(int lh, int rh) {
	int mid = (lh + rh) / 2, i = lh, j = mid + 1, k = 0;
	unit tmp[100];

	while (i <= mid&&j <= rh) {
		
		if (p[i].x < p[j].x) {
			//�ҵ���һ���󲿺��Ҳ��Ľ����
			while (i < mid&&p[i].x < p[j].x&&p[i + 1].x<p[j].x) {
				tmp[k++] = p[i++];
			}
			if (p[i].h < p[j].h) {
				if (i != mid) {
					tmp[k++] = p[i++];
				}
				//�󲿵����һ���㣬����Ҫ���������һ��unit�ĸ߶�0���
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
				//�����󲿵����һ����
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
		//���Ҳ��Ĳ����Ͷ��󲿵Ĳ����෴
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

	//�ϲ����Ҳ�ʣ��Ĳ���
	while (i <= mid) {
		tmp[k++] = p[i++];
	}
	while (j <= rh) {
		tmp[k++] = p[j++];
	}

	//���ϲ����д��ԭ����
	for (i = 0; i <= rh - lh; ++i) {
		p[lh + i] = tmp[i];
	}
}

//�ָ�unit�������
void divide(int lh, int rh) {
	if (rh - lh <= 2) return;	//���䳤��Ϊ2ʱ����Ҫ�����ָ�

	divide(lh, (lh + rh) / 2);	//������
	divide((lh + rh) / 2 + 1, rh);	//�����Ҳ�
	merge(lh, rh);				//�ϲ��󲿺��Ҳ�
}

int main()
{
	ifstream in("in.dat");
	in >> n;
	p = new unit[2 * n];
	//����ÿ������������
	for (int i = 0; i < 2 * n; i += 2) {
		in >> p[i].x >> p[i].h >> p[i + 1].x;
		p[i + 1].h = 0;		//ÿ���������ұ߸߶ȹ̶�Ϊ0
	}

	divide(0, 2 * n - 1);	//���ϲ����
	print(p);				//������

	delete[]p;
	return 0;
}