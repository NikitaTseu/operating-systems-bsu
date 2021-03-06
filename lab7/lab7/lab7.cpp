#include "stdafx.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>

using namespace std;

int n = 4;
mutex mtx;

vector<vector<int> > a = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 8, 7, 6, 5 },{ 4, 3, 2, 1 } };
vector<vector<int> > b = { { 8, 7, 6, 5 },{ 4, 3, 2, 1 },{ 1, 2, 3, 4 },{ 5, 6, 7, 8 } };
vector<vector<int> > ans = { { 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 } };

void func(int lbnd, int rbnd) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int sum = 0;

			for (int k = lbnd; k < rbnd; k++) {
				mtx.lock();
				ans[i][j] += a[i][k] * b[k][j];
				mtx.unlock();
			}
		}
	}
}


int main() {
	thread thr1(func, 0, 2);
	thread thr2(func, 2, 4);
	thr1.join();
	thr2.join();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}