#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
int N;
int A[1001];
//incr[i]: i까지 가장 긴 LIS
//decr[i]: i에서 시작하는 가장 긴 LDS
int incr[1001];
int decr[1001];
//A[end]까지 가장 긴 증가수열 길이 반환
int increase(int end) {
	int& ret = incr[end];
	if (ret != -1) return ret;
	ret = 1;//길이는 최소 1
	for (int i = 0; i <= end; ++i) {
		if (A[end] > A[i])
			ret = max(ret, increase(i) + 1);
	}
	return ret;
}
//A[start]부터 가장 긴 감소수열의 길이 반환
int decrease(int start) {
	int& ret = decr[start];
	if (ret != -1) return ret;
	ret = 1;
	for (int i = start + 1; i < N; ++i)
		if (A[start] > A[i])
			ret = max(ret, decrease(i) + 1);
	return ret;
}
//가장 긴 바이토닉 부분수열 길이반환
//incr[Sk]+decr[Sk]-1
int bitonic() {
	for (int i = 0; i < N; ++i) {
		incr[i] = -1;
		decr[i] = -1;
	}
	int ret = -1;
	for (int Sk = 0; Sk < N; ++Sk) {
		int cand = 0;
		cand += increase(Sk);
		cand += decrease(Sk);
		cand--;
		ret = max(ret, cand);
	}
	return ret;
}
int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);
	printf("%d", bitonic());
}