#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
int n;
int cache[10][101];
int MOD = 1000000000;
//obtimal substructure을 위한 start변수
//첫자리가 start일때, 길이가 length인 계단수의 개수 반환
int stair(int start, int length) {
	//기저1:첫자리가 10
	if (start == 10 || start < 0) return 0;
	//기저2:길이가 1
	if (length == 1) return 1;
	//memoization
	int& ret = cache[start][length];
	if (ret != -1) return ret;
	//stair(start,length) = stair(start+1,length-1) + stair(start-1,length-1)
	ret = 0;
	ret = (ret + stair(start + 1, length - 1)) % MOD;
	ret = (ret + stair(start - 1, length - 1)) % MOD;
	return ret;
}
int main(void) {
	for (int i = 0; i <= 9; ++i)
		for (int j = 0; j <= 100; ++j)
			cache[i][j] = -1;

	scanf("%d", &n);
	int ret = 0;
	for (int start = 1; start <= 9; ++start) {
		ret = (ret + stair(start, n)) % MOD;
	}
	printf("%d", ret);
}
