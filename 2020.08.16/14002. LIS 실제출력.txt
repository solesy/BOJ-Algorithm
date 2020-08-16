#include<iostream>
#include<stdio.h>
#include<vector>
#include<stack>
#include<queue>
#include<list>
#include<string>
#include<algorithm>
#include<cassert>
#include<memory.h>
#include<cmath>
using namespace std;
int n;
bool last[1002];
int a[1002];
int cache[1002];
int choice[1002];
//a[i]이후로 증가하는 숫자의 존재여부를 last에 기록한다.
void calc() {
	int limit = -1;
	int index;
	for (int i = 0; i < n; ++i)
		if (a[i] >= limit) {
			limit = a[i];
			index = i;
		}
	for (int i = 0; i < n; ++i) {
		if (i >= index) last[i] = true;
		if (a[i] == limit) last[i] = true;
		else last[i] = false;
	}
}
//i에서 시작하는 lis의 길이를 반환한다.
int lis(int i) {
	//메모이제이션
	int& ret = cache[i];
	if (ret != -1) return ret;
	ret = 1;
	int bestNext = -1;
	for (int next = i + 1; next < n; ++next)
		if (a[next] > a[i]) {
			int cand = lis(next) + 1;
			if (cand > ret) {
				ret = cand;
				bestNext = next;
			}
		}
	choice[i] = bestNext;
	return ret;
}
//s에서 시작하는 lis를 seq에 저장한다.
void reconstruct(int start, vector<int>& seq) {
	seq.push_back(a[start]);
	int next = choice[start];
	if (next != -1) reconstruct(next, seq);
}
int main(void) {
	memset(cache, -1, sizeof(cache));
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	calc();
	int ans = -1;
	int start;
	for (int i = 0; i < n; ++i) {
		int cand = lis(i);
		if (ans < cand) {
			ans = cand;
			start = i;
		}
	}
	cout << ans << endl;
	vector<int> seq;
	reconstruct(start, seq);
	for (int i = 0; i < seq.size(); ++i)
		cout << seq[i] << " ";
}