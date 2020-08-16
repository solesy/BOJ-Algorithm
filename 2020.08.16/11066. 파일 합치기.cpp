#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string>
#include<cassert>
#include<queue>
#include<memory.h>
using namespace std;
const int MAX = 987654321;
int cache[501][501];
int T, K;
int chapter[501];
int chapterSum[501][501];
//i장부터 j장까지의 합 계산
void calc() {
	for (int i = 1; i <= K; ++i) {
		chapterSum[i][i] = chapter[i];
		for (int j = i + 1; j <= K; ++j)
			chapterSum[i][j] = chapterSum[i][j - 1] + chapter[j];
	}
}
//start장부터 end장까지 크기의 최소비용을 반환한다.
int minCost(int start, int end) {
	//기저: leaf노드에 도달
	if (start == end) return 0;
	//메모이제이션
	int& ret = cache[start][end];
	if (ret != -1)return ret;
	//항상 연속된 두개의 합으로만 이루어지므로
	//minCost(start,end) = min{ minCost(start,k) + minCost(k+1,end) + chapterSum[start][end] }
	ret = MAX;
	for (int k = start; k <= end - 1; ++k)
		ret = min(ret, minCost(start, k) + minCost(k + 1, end) + chapterSum[start][end]);
	return ret;
}
int main(void) {
	vector<int> ans;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> K;
		for (int i = 1; i <= K; ++i)
			cin >> chapter[i];
		calc();
		memset(cache, -1, sizeof(cache));
		ans.push_back(minCost(1, K));
		memset(chapter, 0, sizeof(chapter));
		memset(chapterSum, 0, sizeof(chapter));
	}
	for (int i = 0; i < ans.size(); ++i)
		cout << ans[i] << endl;
}