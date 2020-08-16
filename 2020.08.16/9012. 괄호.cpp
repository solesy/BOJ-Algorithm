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
const string open("(["), close(")]");
//괄호 formula를 입력받아 균형의 여부를 반환한다.
bool balance(const string& formula) {
	stack<char> opening;
	for (int i = 0; i < formula.size(); ++i) {
		//열린 괄호를 스택에 삽입한다.
		if (open.find(formula[i]) != -1)
			opening.push(formula[i]);
		else {
			//pop하면서 닫힌 괄호와 비교한다.
			//닫힌괄호가 먼저 나올경우 스택이 먼저 빈다.
			if (opening.empty()) return false;
			if (open.find(opening.top()) != close.find(formula[i])) return false;
			opening.pop();
		}
	}
	//열린 괄호가 남아있지 않으면 yes
	return opening.empty();
}
int main(void) {
	vector<string> input;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string str;
		cin >> str;
		input.push_back(str);
	}
	for (int i = 0; i < n; ++i)
		balance(input[i]) ? cout << "YES" << endl : cout << "NO" << endl;
}