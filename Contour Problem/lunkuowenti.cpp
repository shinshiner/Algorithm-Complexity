#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int n, *len, **f;

int min(int a, int b) {
	return (a < b ? a : b);
}

int max(int a, int b) {
	return (a > b ? a : b);
}

void merge(int lh, int rh) {
	if (lh >= rh) return;
	int minlen = min(len[lh], len[rh]);
	int maxlen = max(len[lh], len[rh]);
	int *g, *tmp;

	g = new int[maxlen+1];
	for (int i = 1; i <= minlen; ++i) {
		g[i] = max(f[lh][i], f[rh][i]);
	}

	if (len[lh] > len[rh]) {
		for (int i = minlen + 1; i <= maxlen; ++i) {
			g[i] = f[lh][i];
		}
	}
	else {
		for (int i = minlen + 1; i <= maxlen; ++i) {
			g[i] = f[rh][i];
		}
	}

	len[lh] = len[rh] = maxlen;

	tmp = f[lh];
	f[lh] = new int[maxlen+1];
	for (int i = 0; i <= maxlen; ++i)
		f[lh][i] = g[i];
	delete tmp;

	tmp = f[rh];
	f[rh] = new int[maxlen + 1];
	for (int i = 0; i <= maxlen; ++i)
		f[rh][i] = g[i];
	delete tmp;
	delete g;
}

void divide(int lh, int rh) {
	if (lh >= rh) return;

	int mid = (lh + rh) / 2;
	divide(lh, mid);
	divide(mid + 1, rh);
	merge(lh, rh);
}

void trans() {
	int tmp = -1;
	for (int i = 1; i <= len[0]; ++i) {
		if (f[0][i] == tmp) continue;
		else {
			if (i == len[0])
				cout << i;
			else {
				cout << i << ' ' << f[0][i] << ' ';
				tmp = f[0][i];
			}
		}
	}
}

int main()
{
	ifstream in;
	in.open("in.dat");
	ofstream out("out.dat");

	int l, r, h;

	in >> n;
	f = new int*[n];
	len = new int[n];

	for (int i = 0; i < n; ++i) {
		in >> l >> h >> r;
		len[i] = r;
		f[i] = new int[r + 1]{ 0 };
		for (int j = l; j < r; ++j) f[i][j] = h;
	}

	divide(0, n - 1);
	//for (int i = 1; i < len[0]; ++i) cout << f[0][i] << ' '; cout << '\n';
	trans();

	for (int i = 0; i < n; ++i)
		delete[]f[i];
	delete[]f;

	return 0;
}

