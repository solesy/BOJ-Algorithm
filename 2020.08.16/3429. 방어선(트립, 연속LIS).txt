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
struct Node {
	int key, LI;
	//트립: priority
	//LImax: 이 노드를 루트로 하는 서브트리중 LI가 가장 큰것.
	int priority, LImax;
	Node* left, * right;
	Node(const int& _key, const int& _LI) :key(_key), LI(_LI), priority(rand()), LImax(_LI),left(NULL),right(NULL) {}
	//LImax를 계산한다.
	void calcLImax() {
		LImax = LI;
		if (left != NULL)
			LImax = max(LImax, left->LImax);
		if (right != NULL)
			LImax = max(LImax, right->LImax);
	}
	void setLeft(Node* newLeft) { left = newLeft; calcLImax(); }
	void setRight(Node* newRight) { right = newRight; calcLImax(); }
};
//root를 노드로 하는 트립을 
//key미만의 값을 가진 트립과, key초과의 값을 가진 트립으로 나누어 반환한다.
typedef pair<Node*, Node*> NodePair;
NodePair split(Node* root, int key) {
	if (root == NULL) return NodePair(NULL, NULL);
	//root의 값이 key미만인 경우 root의 오른쪽 서브트리을 나눈다.
	if (root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	else if (root->key > key){
		NodePair ls = split(root->left, key);
		root->setLeft(ls.second);
		return NodePair(ls.first, root);
	}
}
//root를 루트로하는 트립에 node를 삽입한 루트를 반환한다.
Node* insert(Node* root, Node* node) {
	//기저1: node의 우선순위가 낮아 leaf까지 도달한 경우
	if (root == NULL) return node;
	//기저2: node의 우선순위가 root의 우선순위보다 큰 경우 split을 사용한다.
	if (root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	//node의 값이 더 클경우, root의 오른쪽 서브트리에 삽입한다.
	else if (root->key < node->key)
		root->setRight(insert(root->right, node));
	else if (root->key > node->key)
		root->setLeft(insert(root->left, node));
	return root;
}
//root를 루트로 하는 트립에 node가 있는지 여부를 반환한다.
bool isExist(Node* root, Node* node) {
	if (root == NULL) return false;
	if (root->key == node->key) return true;
	else if (root->key > node->key) return isExist(root->left, node);
	else return isExist(root->right, node);
}
//트립에 이미 node의 값이 있을 경우만 호출한다.
//LI가 더 높은 노드만 존재하게 한다. 그 후, 트립의 루트를 반환한다.
Node* erase(Node* root, Node* node) {
	if (root->key == node->key) {
		if (root->LI >= node->LI) return root;
		//기존의 LI값이 더 작다면
		else {
			node->setLeft(root->left);
			node->setRight(root->right);
			delete root;
			return node;
		}
	}
	if (root->key > node->key)
		root->setLeft(erase(root->left, node));
	else if (root->key < node->key)
		root->setRight(erase(root->right, node));
	return root;
}
//root를 루트로 하는 트립과 root에 속한 노드 node가 주어질때,
//node보다 큰 노드들 중 가장 높은 LI를 반환한다.
int findLImax(Node* root, Node* node) {
	//기저: node를 찾았을때 
	if (root->key == node->key) {
		if (root->right == NULL) return 0;
		else return root->right->LImax;
	}
	int ret = 0;
	//root의 값이 node보다 큰 경우
	if (root->key > node->key) {
		//root의 LI와 root->right의 LImax를 고려한다.
		if (root->right != NULL)
			ret = root->right->LImax;
		ret = max(ret, root->LI);
		//왼쪽 서브트리에서 node보다 큰 LI를 찾는다.
		ret = max(ret, findLImax(root->left, node));
	}
	//root의 값이 node보다 작은 경우
	else
		ret = findLImax(root->right, node);
	return ret;
}
/*void printinord(Node* root) {
	if (root == NULL) return;
	printinord(root->left);
	printf("노드는 %d 이고 LImax는 %d\n",root->key, root->LImax);
	printinord(root->right);
}*/
void deleteTree(Node* root) {
	if (root == NULL) return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}
int main(void) {
	int tc;
	scanf("%d", &tc);
	vector<int> t;
	while (tc != 0) {
		int n;
		scanf("%d", &n);
		vector<int> a(n);
		for (int i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		//LI[i]: a[i]부터 시작하는 가장 긴 연속증가 타워의 길이
		vector<int> LI(n);
		LI[n - 1] = 0;
		for (int i = n - 2; i >= 0; --i)
			LI[i] = (a[i] < a[i + 1] ? LI[i + 1] + 1 : 0);
		//Longest[i]: a[i]부터 시작하는, 
		//한번만 연속삭제해서 얻을수 있는 가장 긴 연속증가 타워의 길이
		vector<int> Longest(n);
		Longest[n - 1] = 0;
		//a[n-1]부터 트립에 insert한다.
		Node* root = new Node(a[n - 1], LI[n - 1]);
		for (int i = n - 2; i >= 0; --i) {
			Node* node = new Node(a[i], LI[i]);
			//root에 node를 삽입한다.
			if (isExist(root, node))
				//LI가 더 큰 노드만을 남긴다.
				root = erase(root, node);
			else
				root = insert(root, node);
			//node보다 큰 타워들 중 가장 높은 LI를 구한다.
			int LImax = findLImax(root, node);
			//i에서 바로 연속삭제하는경우
			Longest[i] = LImax != 0 ? LImax + 1 : 0;
			//a[i] a[i+1]이 연속증가라면, 당장 연속삭제를 할 필요는 없다
			if (LI[i] == LI[i + 1] + 1)
				Longest[i] = max(Longest[i], Longest[i + 1] + 1);
		}
		deleteTree(root);
		int ans = -1;
		for (int i = 0; i < n; ++i)
			ans = max(ans, Longest[i]);
		t.push_back(ans + 1);
		--tc;
	}
	for (int i = 0; i < t.size(); ++i)
		printf("%d\n", t[i]);
}