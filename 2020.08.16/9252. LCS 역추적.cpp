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
string a, b;
//재귀의 내부는 O(1)만에 돌아가야 하므로, 
//choice에는 a,b값이 서로 같을 경우만의 cache를 저장한다.
int choice[1001][1001];
int cache[1001][1001];
//aIndex,bIndex 또는 그 이후의 lcs의 길이를 반환한다.
int lcs(int aIndex, int bIndex) {
	//기저: aIndex=a.size, bIndex=b.size
	if (aIndex == a.size() || bIndex == b.size()) return 0;
	//메모이제이션
	int& ret = cache[aIndex][bIndex];
	if (ret != -1) return ret;
	int choose = -1;
	ret = max(ret, lcs(aIndex + 1, bIndex));
	ret = max(ret, lcs(aIndex, bIndex + 1));
	//값이 서로 같은경우 lcs에 속할 가능성이 있다.
	if (a[aIndex] == b[bIndex] && lcs(aIndex + 1, bIndex + 1) + 1 > ret) {
		ret = lcs(aIndex + 1, bIndex + 1) + 1;
		choose = ret;
	}
	choice[aIndex][bIndex] = choose;
	return ret;
}
//a[aIndex], b[bIndex] 부터 시작하는 length 길이의 lcs를 seq에 저장한다.
//choice가 항상 lcs일 경우만 추적한다.
void reconstruct(string& seq) {
	int prevA = -1, prevB = -1;
	int length = cache[0][0];
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < b.size(); ++j) {
			if (choice[i][j] == length && i > prevA && j > prevB) {
				prevA = i;
				prevB = j;
				--length;
				seq.push_back(a[i]);
			}
		}
	}
}
int main(void) {
	memset(cache, -1, sizeof(cache));
	memset(choice, -1, sizeof(cache));
	cin >> a;
	cin >> b;
	cout << lcs(0, 0) << endl;
	string seq;
	reconstruct(seq);
	for (int i = 0; i < seq.size(); ++i)
		cout << seq[i];
}