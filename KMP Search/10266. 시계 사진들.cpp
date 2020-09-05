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
//p[i]: N[...i]의 접두사 = N[...i]의 접미사를 만족하는 최대길이
//를 구해서 반환한다.
vector<int> getFailureArray(const vector<int>& N) {
	int n = N.size();
	vector<int> p(n, 0);
	//N과 N을 비교한다.
	//begin과 match는 절대 줄어들지 않고 루프당 둘중 하나는 무조건 늘어나므로 o(2n)
	for (int begin = 1, match = 1; match < n;) {
		//일치할 경우 부분일치를 구한다.
		while (N[match] == N[match - begin]) {
			p[match] = match - begin + 1;
			++match;
		}
		//일치하지 않는경우
		if (N[match] != N[match - begin]) {
			//begin을 점프시킬 수 없는경우
			if (begin == match) {
				++begin;
				++match;
			}
			//begin을 점프시킨다.
			//match에서 빼는건 양쪽에 3개 3개씩 일치하는 예시 생각
			//kmp가 안될거같은 생각날땐 하나도 일치하지 않는 경우 생각(begin부터 N을 옮겨본다)
			else
				begin = match - p[match - begin - 1];
		}
	}
	return p;
}
//H에서 N이 있는지의 여부를 반환한다.
bool kmpSearch(const vector<int>& H, const vector<int>& N) {
	int begin = 1, match = 1;
	vector<int> p = getFailureArray(N);
	while (match < H.size()) {
		//일치하는 경우
		if (H[match] == N[match - begin]) {
			++match;
			//N이 있는경우
			if (match - begin == N.size())
				return true;
		}
		//일치하지 않는 경우
		else {
			if (begin == match) {
				++begin;
				++match;
			}
			//begin을 점프시킨다
			else
				begin = match - p[match - begin - 1];
		}
	}
	return false;
}
int main(void) {
	int n;
	scanf("%d", &n);
	vector<int> input1(n), input2(n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &input1[i]);
	for (int i = 0; i < n; ++i)
		scanf("%d", &input2[i]);
	//시계침사이의 각도들을 clock배열을 이용하여 나타낸다.
	sort(input1.begin(), input1.end());
	sort(input2.begin(), input2.end());
	vector<int> clock1(2*n), clock2(n);
	for (int i = 0; i < n; ++i) {
		if (i == n - 1) {
			clock1[i] = (360000 + input1[0]) - input1[i];
			clock1[2 * n - 1] = clock1[n - 1];
			clock2[i] = (360000 + input2[0]) - input2[i];
		}
		else {
			clock1[i] = input1[i + 1] - input1[i];
			clock1[n + i] = clock1[i];
			clock2[i] = input2[i + 1] - input2[i];
		}
	}
	//clock1(H)에서 clock2(N)를 찾는다.(kmp알고리즘)
	kmpSearch(clock1, clock2) == true ? printf("possible") : printf("impossible");
}