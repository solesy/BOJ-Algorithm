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
struct UnionFind {
	//연결관계를 표현하는 parent
	//rank[i]: 루트인 i의 랭크
	vector<int> parent, rank;
	//init
	UnionFind(int n) {
		parent.resize(n);
		rank.resize(n, 1);
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}
	//find
	//u가 속한 트리의 루트를 반환한다.
	int find(int u) {
		if (parent[u] == u) return u;
		//경로압축
		return parent[u] = find(parent[u]);
	}
	//union
	//u가 속한 집합과 v가 속한 집합을 합친다.
	void merge(int u, int v) {
		u = find(u); v = find(v);
		//불변식: rank[u] < rank[v], 항상 v에 u가 서브트리로 들어간다.
		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		//rank가 증가하는 경우는 합쳤던 u와 v의 높이가 같았을때 뿐이다.
		if (rank[u] == rank[v]) ++rank[v];
	}
};
int main(void) {
	int n, m;
	scanf("%d%d", &n, & m);
	UnionFind uf(n + 1);
	vector<string> ret;
	for (int i = 0; i < m; ++i) {
		int k, a, b;
		scanf("%d%d%d", &k, &a, &b);
		if (k == 0) uf.merge(a, b);
		else
			(uf.find(a) == uf.find(b)) ? ret.push_back("YES\0") : ret.push_back("NO\0");
	}
	for (int i = 0; i < ret.size(); ++i)
		printf("%s\n", ret[i].c_str());
}
