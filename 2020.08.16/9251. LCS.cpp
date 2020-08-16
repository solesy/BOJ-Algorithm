#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string>
#include<cassert>
#include<queue>
#include<memory.h>
using namespace std;
string A;
string B;
int cache[1001][1001];
//A[i],B[j] 또는 그 이후의 최장 공통 부분 수열의 길이를 반환한다.
int LCS(int i, int j) {
	//기저
	if (i == A.size() || j == B.size()) return 0;
	//메모이제이션
	int& ret = cache[i][j];
	if (ret != -1) return ret;
	//i,j를 고르는 경우
	if (A[i] == B[j]) 
		ret = max(ret, 1 + LCS(i + 1, j + 1));
	//각각 i또는 j를 건너뛰는 경우
	ret = max(ret, LCS(i + 1, j + 1));
	ret = max(ret, LCS(i + 1, j));
	ret = max(ret, LCS(i, j + 1));
	return ret;
}
int main(void) {
	cin >> A;
	cin >> B;
	memset(cache, -1, sizeof(cache));
	cout << LCS(0, 0) << endl;
}