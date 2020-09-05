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
#include <time.h>
using namespace std;
//p[i]: N[...i]접두사 = N[...i]접미사 최대길이
vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	int begin = 1, match = 1;
	vector<int> pi(m, 0);
	while (match < m) {
		if (N[match] == N[match - begin]) {
			pi[match] = match - begin + 1;
			++match;
		}
		else {
			if (begin == match) {
				++begin;
				++match;
			}
			//begin을 점프시킨다.
			else
				begin = match - pi[match - begin - 1];
		}
	}
	return pi;
}
vector<int> kmpSearch(const string& H, const string& N) {
	int m = H.size(), n = N.size();
	int begin = 0, match = 0;
	vector<int> ret;
	vector<int> pi = getPartialMatch(N);
	while (match < m) {
		if (match - begin < n && H[match] == N[match - begin]) {
			++match;
			//문자열이 전부 매칭됬으면
			if (match - begin == n) ret.push_back(begin);
		}
		else {
			if (begin == match) {
				++begin;
				++match;
			}
			//begin을 점프시킨다.
			else
				begin = match - pi[match - begin - 1];
		}
	}
	return ret;
}
int main(void) {
	string H, N;
	getline(cin, H);
	getline(cin, N);
	vector<int> ans = kmpSearch(H, N);
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); ++i)
		cout << ans[i] + 1 << " ";
}