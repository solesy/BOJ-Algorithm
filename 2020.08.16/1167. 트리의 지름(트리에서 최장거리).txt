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
struct TreeNode {
	vector<TreeNode*> children;
	vector<int> weight;
};
int n;
vector<pair<int, int>> edges[100002];
//leaf-leaf거리의 최대
int longest;
//각 노드의 방문여부 visited가 주어질때,
//root를 루트로 하는 트리의 최대가중치를 반환한다.
int weight(int root, vector<bool>& visited) {
	visited[root] = true;
	//각 자식들을 루트로 하는 서브트리의 가중치+
	//root->i으로 가는 가중치를 구한다.
	vector<int> w;
	for (int i = 0; i < edges[root].size(); ++i) {
		int child = edges[root][i].first;
		//child가 아니다.
		if (visited[child]) continue;
		visited[child] = true;//한 노드는 두번다시 들리지 않는다.
		w.push_back(weight(child, visited) + edges[root][i].second);
	}
	//자식이 하나도 없다면 0을 반환한다.
	if (w.size() == 0) return 0;
	//w에서 제일 큰 값을 구한다.
	int maxw1 = 0;
	int maxi1;
	for (int i = 0; i < w.size(); ++i)
		if (w[i] > maxw1) {
			maxw1 = w[i];
			maxi1 = i;
		}
	//자식이 2명이상일 경우, leaf-leaf를 잇는것이 가능하다.
	if (w.size() >= 2) {
		//w에서 두번째로 큰 값을 구한다.
		int maxw2 = 0;
		int maxi2;
		for (int i = 0; i < w.size(); ++i)
			if (i != maxi1 && w[i] > maxw2) {
				maxw2 = w[i];
				maxi2 = i;
			}
		longest = max(longest, maxw1 + maxw2);
	}
	return maxw1;
}
int main(void) {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int node;
		cin >> node;
		while (1) {
			int next, weight;
			cin >> next;
			if (next == -1) break;
			cin >> weight;
			edges[node].push_back(make_pair(next, weight));
		}
	}
	//visited시작은 모두 false
	vector<bool> visited(n + 2, false);
	//root-leaf, leaf-leaf 중에 트리의 지름은 존재한다.
	int ans = max(weight(2, visited), longest);
	cout << ans;
}