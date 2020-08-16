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
	vector<string> sentence;
	string temp;
	while (temp != ".") {
		getline(cin, temp);
		input.push_back(temp);
	}
	input.pop_back();
	for (int i = 0; i < input.size(); ++i) {
		string oc;
		for (int j = 0; j < input[i].size(); ++j)
			//괄호만 걸러내서 sentence에 저장한다.
			if (open.find(input[i][j]) != -1 || close.find(input[i][j]) != -1)
				oc.push_back(input[i][j]);
		sentence.push_back(oc);
	}
	for (int i = 0; i < sentence.size(); ++i)
		balance(sentence[i]) ? cout << "yes" << endl : cout << "no" << endl;
}