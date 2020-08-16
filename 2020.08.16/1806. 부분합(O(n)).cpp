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
const int INF = 987654321;
//수열 n에서 부분합이 s이상인것 중 최소의 길이를 반환한다.
int length(vector<int>& n, int s) {
	int tail = 0, rangeSum = n[0], ret = INF;
	//부분합이 s이상이 되는 순간의 부분구간을 구한다.
	for (int head = 0; head < n.size(); ++head) {
		//tail은 단조증가한다.
		while (rangeSum < s && tail < n.size() - 1)
			rangeSum += n[++tail];
		if (rangeSum >= s) ret = min(ret, tail - head + 1);
		rangeSum -= n[head];
	}
	return ret;
}
int main(void) {
	int l, s;
	vector<int> n;
	scanf("%d %d", &l, &s);
	for (int i = 0; i < l; ++i) {
		int temp;
		scanf("%d", &temp);
		n.push_back(temp);
	}
	int ans = length(n, s);
	if (ans == INF)
		printf("0");
	else {
		printf("%d", ans);
	}
}