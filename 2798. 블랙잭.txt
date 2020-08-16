#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
int N, M;
int card[101];
//picked: 지금까지 고른 카드 저장
//M과 가장 가까운 카드3장의 합을 반환한다.
int solve(vector<int>& picked) {
	//기저: 3장을 다고름
	if (picked.size() == 3) {
		int sum = 0;
		for (int i = 0; i < 3; ++i)
			sum += card[picked[i]];
		//sum이 M보다 작거나같을경우 sum을, 아닐경우 -1을 반환
		return sum <= M ? sum : -1;
	}
	int pickCard = picked.empty() ? 0 : picked.back() + 1;
	int ret = -1;
	for (; pickCard < N; ++pickCard) {
		picked.push_back(pickCard);
		ret = max(ret, solve(picked));
		picked.pop_back();
	}
	return ret;
}
int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	vector<int> picked;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i) scanf("%d", &card[i]);
	printf("%d", solve(picked));
}