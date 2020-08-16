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
int n, w;
vector<pair<int, int>> casePos;//0번사건, w+1사건도 고려해야
int cache[1005][1005];
//first, second가 주어질때, 이동거리의 최소를 저장한다.
int choice[1005][1005];
//1경찰차가 마지막으로 해결한 사건 one,
//2경찰차가 마지막으로 해결한 사건 two가 주어질 때,
//남은 사건을 해결할때의 두 경찰차의 이동거리의 최소를 반환한다.
int minMove(int one, int two) {
	//기저: 모든사건을 해결했을때
	if (one == w || two == w) {
		choice[one][two] = 0;
		return 0;
	}
	//메모이제이션
	int& ret = cache[one][two];
	if (ret != -1) return ret;
	ret = 0;
	int nextCase;
	if (two == w + 1)//2경찰차가 한번도 안움직였다면
		nextCase = one + 1;
	else
		nextCase = max(one + 1, two + 1);
	//dist1: 다음사건과 1경찰차 사이의 거리
	//dist2: 다음사건과 2경찰차 사이의 거리
	int dist1 = abs(casePos[nextCase].first - casePos[one].first)
		+ abs(casePos[nextCase].second - casePos[one].second);
	int dist2 = abs(casePos[nextCase].first - casePos[two].first)
		+ abs(casePos[nextCase].second - casePos[two].second);
	//1경찰차를 우선 움직여본다.
	ret = dist1 + minMove(nextCase, two);
	choice[one][two] = ret;
	//2경찰차를 움직여보고,
	//1경찰차를 움직인것보다 값이 더 좋다면 그것으로 바꾼다.
	int cand = dist2 + minMove(one, nextCase);
	if (cand <= ret) {
		ret = cand;
		choice[one][two] = cand;
	}
	return ret;
}
//seq[i]: i번사건을 해결한 경찰차
void reconstruct(vector<int>& seq) {
	int one = 0, two = w + 1;
	while (seq.size() != w) {
		int nextCase;
		if (two == w + 1)
			nextCase = one + 1;
		else
			nextCase = max(one + 1, two + 1);
		//1경찰차가 다음사건을 해결할때의 나올수 있는 최소거리
		int t1 = abs(casePos[nextCase].first - casePos[one].first)
			+ abs(casePos[nextCase].second - casePos[one].second) + choice[nextCase][two];
		//2경찰차가 다음사건을 해결할때의 나올수 있는 최소거리
		int t2 = abs(casePos[nextCase].first - casePos[two].first)
			+ abs(casePos[nextCase].second - casePos[two].second) + choice[one][nextCase];
		if (t1 < t2) {
			seq.push_back(1);
			one = nextCase;
		}
		else {
			seq.push_back(2);
			two = nextCase;
		}
	}
}
int main(void) {
	memset(cache, -1, sizeof(cache));
	for (int i = 0; i < 1005; ++i)
		for (int j = 0; j < 1005; ++j)
			choice[i][j] = INF;
	casePos.push_back(make_pair(1, 1));//0번사건의 위치는 (1,1)
	scanf("%d %d", &n, &w);
	for (int i = 1; i <= w; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		casePos.push_back(make_pair(a, b));//1~w사건
	}
	casePos.push_back(make_pair(n, n));//w+1사건
	printf("%d\n", minMove(0, w + 1));
	vector<int> seq;
	reconstruct(seq);
	for (int i = 0; i < seq.size(); ++i)
		printf("%d\n", seq[i]);
}