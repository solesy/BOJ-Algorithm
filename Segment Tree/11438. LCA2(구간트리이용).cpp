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
struct RMQ {
	//배열의 길이
	int n;
	//segment tree
	vector<int> rangeMin;
	const int MaxInt = 9876543210;
	RMQ(const vector<int>& array) {
		n = array.size();
		//n과 가장가까운 2의제곱수 k, k<2n => 2k<4n
		rangeMin.resize(4 * n);
		//구간트리 생성
		init(array, 1, 0, n - 1);
	}
	//array[left...right]구간을 나타내는 노드번호 node가 주어질때,
	//양쪽 서브구간트리를 초기화하고 최솟값을 반환한다.
	int init(const vector<int>& array, int node, int left, int right) {
		//기저: leaf에 도달했을때
		if (left == right) return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int minLeft = init(array, 2 * node, left, mid);
		int minRight = init(array, 2 * node + 1, mid + 1, right);
		return rangeMin[node] = min(minLeft, minRight);
	}
	//원하는구간 array[left...right]와 node가 나타내는 구간 node[nodeLeft...nodeRight]과의
	//교집합의 최소를 반환한다.
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		//case1: 교집합이 공집합인 경우
		if (left > nodeRight || right < nodeLeft) return MaxInt;
		//case2: 원하는구간 -) 노드의구간
		if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];
		//case3,4: 원하는구간 (- 노드의구간, 부분교집합이 존재하는 경우
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, 2 * node, nodeLeft, mid),
			query(left, right, 2 * node + 1, mid + 1, nodeRight));
	}
};
const int max_n = 100002;
int n;
vector<int> child[max_n];
//노드와 일련번호(전위순회 방문순서)의 상관관계 
int node2serial[max_n], serial2node[max_n];
//trip은 일련번호로 저장된다.(부모일련번호 < 자식일련번호)
vector<int> trip;
//locInTrip[u]: trip에서 일련번호값에 대응되는 노드의값 u가 처음 나오는 위치
int locInTrip[max_n];
int nextSerial;
//노드 here을 루트로하는 서브트리를 전회순회하며 trip을 초기화한다.
void traverse(int here, vector<bool>& visited) {
	//trip, 일련번호 등을 기록한다.
	visited[here] = true;
	node2serial[here] = nextSerial;
	serial2node[nextSerial] = here;
	locInTrip[here] = trip.size();
	trip.push_back(node2serial[here]);
	++nextSerial;
	//자식들을 전위순회한다.
	for (int i = 0; i < child[here].size(); ++i) {
		int next = child[here][i];
		//이미 방문한것인 경우 부모이므로 건너뛴다.
		if (visited[next]) 
			continue;
		traverse(child[here][i], visited);
		//돌아오는길에도 trip을 기록한다.
		trip.push_back(node2serial[here]);
	}
}
int main(void) {
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		child[u].push_back(v);
		child[v].push_back(u);
	}
	//trip의 구간에서의 최솟값이 구간에서의 최상위노드이다.
	//trip의 구간트리 rmq를 생성한다.
	vector<bool> visited(n + 1, false);
	traverse(1, visited);
	RMQ rmq(trip);
	int q;
	scanf("%d", &q);
	vector<int> ans;
	for (int i = 0; i < q; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		//u와 v가 trip에서 처음 등장하는 위치를 찾는다
		int lu = locInTrip[u], lv = locInTrip[v];
		if (lu > lv) swap(lu, lv);
		int lca = serial2node[rmq.query(lu, lv, 1, 0, trip.size() - 1)];
		ans.push_back(lca);
	}
	for (int i = 0; i < ans.size(); ++i)
		printf("%d\n", ans[i]);
}