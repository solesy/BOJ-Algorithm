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
#include<map>
using namespace std;
const int INF = 1234567890;
typedef pair<int, int> Point;//<x,y>
vector<Point> coords;
//y에대해 오름차순으로 정렬할때 사용한다.
bool compare(Point& a, Point& b) {
	if (a.second != b.second) return a.second < b.second;
	else return a.first < b.first;
}
//a,b사이의 거리의 제곱을 반환한다.
int dist(Point& a, Point& b) {
	int p = abs(a.first - b.first);
	int q = abs(a.second - b.second);
	return p * p + q * q;
}
//coords[i]부터 n개의 좌표가 있을 때,
//점들간의 최소거리를 반환한다.(lgn번 호출)
int findMinDist(int i, int n) {
	//기저
	if (n == 1) return INF;
	if (n == 2) return dist(coords[i], coords[i + 1]);
	//i부터 n/2 개의 최소거리, i+n/2 부터 n-n/2 개의 최소거리를 구한다.
	int minLeft = findMinDist(i, n / 2);
	int minRight = findMinDist(i + n / 2, n - n / 2);
	int cand = min(minLeft, minRight);
	//midLane을 가로지르는 최소거리를 구한 후, cand와 비교하여 최소를 함수에서 반환한다.
	int midLane = (coords[i + n / 2 - 1].first + coords[i + n / 2].first) / 2;
	//midLane을 기준으로 cand범위 안에 있는 점들만을 고른다.(나머진 가능성업다)
	vector<Point> picked;
	for (int j = i; j < i + n; ++j) {
		int len = abs(midLane - coords[j].first);
		if (len * len <= cand) 
			picked.push_back(coords[j]);
	}
	//y좌표에 대해 오름차순으로 정렬
	sort(picked.begin(), picked.end(), compare);
	//picked의 midLane을 가로지르는 두점에 대해,
	//거리가 cand보다 작아지기 위해서는 반대편의 점이 cand*2cand 직사각형 범위 내에 있어야한다.
	//y좌표가 작은것부터 처리하면 y보다 크고 인접한 6개만 고려하면된다.
	for (int j = 0; j < picked.size(); ++j)
		for (int k = 1; k <= 6; ++k)
			if (j + k < picked.size())
				//굳이 midLane을 가로지르는 경우를 제한하지 않아도,
				//가로지르지 않는 경우는 항상 cand보다 크거나 같다.
				cand = min(cand, dist(picked[j], picked[j + k]));
	return cand;
}
int main(void) {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		coords.push_back(make_pair(x, y));
	}
	sort(coords.begin(), coords.end());
	printf("%d", findMinDist(0, n));
}