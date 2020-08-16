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
#include<map>
using namespace std;
//p[i]: a[...i]의 앞뒤계수의 최대값
vector<int> getPartialMatchFunc(const vector<int>& a) {
	int n = a.size();
	int begin = 1, match = 1;
	vector<int> pi(n, 0);
	//begin,match를 증가시키면서 최대부분일치 길이를 구한다.
	while (match < n) {
		//부분일치할 경우
		if (a[match] == a[match - begin]) {
			//a[...match]까지 앞뒤가 일치한다.
			pi[match] = match - begin + 1;
			++match;
		}
		else {
			//반복문 불변식: match>=begin
			if (match == begin) {
				++match;
				++begin;
			}
			else//begin을 이동시킨다.
				begin = match - pi[match - 1 - begin];
		}
	}
	return pi;
}
int main(void) {
	int n;
	scanf("%d", &n);
	vector<int> input(n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &input[n - i - 1]);
	vector<int> p = getPartialMatchFunc(input);
	int maxLen = -1;
	for (int i = 0; i < n; ++i)
		maxLen = max(maxLen, p[i]);
	int count = 0;
	if (maxLen == 0) maxLen = -1;
	else
		for (int i = 0; i < n; ++i)
			if (p[i] == maxLen) ++count;
	maxLen == -1 ? printf("-1") : printf("%d %d", maxLen, count);
}