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
//n개의 원판을 from에서 to로 옮긴다.
//그 순서를 출력한다.
void hanoi(int from, int notUse, int to, int n) {
	//기저: 1개의 원판은 아무데도 안거쳐도 된다.
	if (n == 1) { 
		printf("%d %d\n", from, to);
		return;
	}
	//젤 큰수만 뺴고 a->b로 옮긴다.
	hanoi(from, to, notUse, n - 1);
	hanoi(from, notUse, to, 1);
	//똑같은 방식으로 b->c로 옮긴다.
	hanoi(notUse, from, to, n - 1);
	return;
}
//출력 순서때문에 하나 더 만든다. hanoi함수랑 작동방식 동일
int hanoiCount(int from, int notUse, int to, int n) {
	//기저: 1개의 원판은 아무데도 안거쳐도 된다.
	if (n == 1) return 1;
	int ret = 0;
	//젤 큰수만 뺴고 a->b로 옮긴다.
	ret += hanoiCount(from, to, notUse, n - 1);
	ret += hanoiCount(from, notUse, to, 1);
	//똑같은 방식으로 b->c로 옮긴다.
	ret += hanoiCount(notUse, from, to, n - 1);
	return ret;
}
int main(void) {
	int k;
	scanf("%d", &k);
	printf("%d\n", hanoiCount(1, 2, 3, k));
	hanoi(1, 2, 3, k);
}