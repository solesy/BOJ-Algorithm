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
typedef long long ll;
//펜윅트리로 해결하는 방법
struct FenwickTree {
	//tree[i]: 펜윅트리그림에서 오른쪽끝이 A[i]인 구간의 합
	vector<ll> tree;
	//n: 수의 개수
	FenwickTree(int n) :tree(n + 1) {}
	//A[...pos]까지의 부분합을 구한다.
	ll sum(int pos) {
		ll ret = 0;
		//pos는 2^i의 배수지만 2^(i+1)의 배수는 아니다. 구간 길이는 2^i고
		//이 길이를 빼면서 부분합을 구한다.
		while (pos > 0) {
			ret += tree[pos];
			pos = (pos - 1) & pos;
		}
		return ret;
	}
	//A[pos]에다 val을 더한다.
	void add(int pos, ll value) {
		while (pos < tree.size()) {
			tree[pos] += value;
			int lowestBit = pos & ((~pos) + 1);
			pos += lowestBit;
		}
	}
};
//구간트리를 이용하여 해결
struct SegmentTree {
	//수의 개수
	int n;
	vector<ll> tree;
	SegmentTree(const vector<ll>& array) {
		n = array.size();
		tree.resize(4 * n);
		init(array, 1, 1, n - 1);
	}
	//node가 array[left...right]구간을 나타내는 노드번호일때
	//node를 루트로하는 구간트리를 초기화하고 구간의 합을 반환한다.
	ll init(const vector<ll>& array, int node, int left, int right) {
		if (left == right) return tree[node] = array[left];
		int mid = (left + right) / 2;
		ll leftSum = init(array, 2 * node, left, mid);
		ll rightSum = init(array, 2 * node + 1, mid + 1, right);
		return tree[node] = leftSum + rightSum;
	}
	//원하는 구간 array[left...right]와 node의 구간 array[nodeLeft...nodeRight]의
	//교집합에서의 합을 반환한다.
	ll query(int left, int right, int node, int nodeLeft, int nodeRight) {
		//case1: 공집합인 경우
		if (left > nodeRight || right < nodeLeft) return 0;
		//case2: 원하는구간 -) 노드의구간
		if (left <= nodeLeft && nodeRight <= right) return tree[node];
		//case3,4: 원하는구간(- 노드의구간, 부분교집합이 존재하는 경우
		int mid = (nodeLeft + nodeRight) / 2;
		ll leftSum = query(left, right, 2 * node, nodeLeft, mid);
		ll rightSum = query(left, right, 2 * node + 1, mid + 1, nodeRight);
		return leftSum + rightSum;
	}
	//array[index]=newValue로 바꾼 후,
	//node를 루트로 하는 서브트리의 값을 반환한다.
	ll update(int index, int newValue, int node, int left, int right) {
		if (index < left || right < index) return tree[node];
		if (left == right) return tree[node] = newValue;
		int mid = (left + right) / 2;
		return tree[node] = update(index, newValue, 2 * node, left, mid)
			+ update(index, newValue, 2 * node + 1, mid + 1, right);
	}
};
int main(void) {
	int n, u, q;
	scanf("%d%d%d", &n, &u, &q);
	vector<ll> input(n + 1);
	for (int i = 1; i <= n; ++i)
		scanf("%lld", &input[i]);
	/*
	//펜윅트리를 이용하여 문제 해결
	FenwickTree fenwickTree(n);
	//펜윅트리를 초기화한다.
	for (int i = 1; i <= n; ++i)
		fenwickTree.add(i, input[i]);
	vector<ll> ans;
	//update되기전의 input값
	vector<ll> prevInput(n + 1);
	for (int i = 0; i < u + q; ++i) {
		ll a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		//a==1이면 updates, 2이면 query를 실행한다.
		if (a == 1) {
			prevInput[b] = input[b];
			input[b] = c;
			fenwickTree.add(b, input[b] - prevInput[b]);
		}
		else
			ans.push_back(fenwickTree.sum(c) - fenwickTree.sum(b - 1));
	}
	for (int i = 0; i < ans.size(); ++i)
		printf("%lld\n", ans[i]);
	*/
	SegmentTree tree(input);
	vector<ll> ans;
	for (int i = 0; i < u + q; ++i) {
		ll a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		//a==1이면 updates, 2이면 query를 실행한다.
		if (a == 1)
			tree.update(b, c, 1, 1, n);
		else
			ans.push_back(tree.query(b, c, 1, 1, n));
	}
	for (int i = 0; i < ans.size(); ++i)
		printf("%lld\n", ans[i]);
}