#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string>
#include<cassert>
using namespace std;
const int MAX_N = 15;
vector<string> input;
int n, k;
long long cache[1 << 15][101];
long long fac[MAX_N + 1];
int inputMods[MAX_N];//input%k
int powerMods[101][51];//(i*10^j)%k
//n!���� ���
//��� ����� ��
void factorial() {
	fac[1] = 1;
	for (int i = 2; i <= n; ++i)
		fac[i] = i * fac[i - 1];
}
//temp�� K�� ���� �������� ��ȯ�Ѵ�.
int modula(string temp) {
	int ret = 0;
	for (int i = 0; i < temp.size(); ++i)
		ret = (ret * 10 + (temp[i] - '0')) % k;
	return ret;
}
//���ݱ��� ����� ���� visited,
//���ݱ��� ������� k�� ���� �������� mod �϶�,
//��ģ���� k�� ������ �������� ��� ������ ����� ���� ��ȯ�Ѵ�.
long long solve(int visited, int mod) {
	//����
	if (visited == ((1 << n) - 1)) return mod == 0 ? 1 : 0;
	//�޸������̼�
	long long& ret = cache[visited][mod];
	if (ret != -1) return ret;
	ret = 0;
	//�̹��� ����� �� here�� ���Ѵ�.
	for (int i = 0; i < n; ++i) {
		if ((visited & (1 << i)) == 0) {
			int here = i;
			int nextVisited = visited | (1 << i);
			int nextMod = (powerMods[mod][input[here].size()] + inputMods[here]) % k;
			ret += solve(nextVisited, nextMod);
		}
	}
	return ret;
}
long long gcd(long long p, long long s) {
	return s == 0 ? p : gcd(s, p % s);
}
int main(void) {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string str;
		cin >> str;
		input.push_back(str);
	}
	cin >> k;
	for (int i = 0; i < (1 << 15); ++i)
		for (int j = 0; j < 100; ++j)
			cache[i][j] = -1;
	for (int i = 0; i < n; ++i)
		inputMods[i] = modula(input[i]);
	for (int i = 0; i < 100; ++i) {
		string p = "0";
		for (int j = 1; j < 51; ++j) {
			string temp = to_string(i) + p;
			powerMods[i][j] = modula(temp);
			p += "0";
		}
	}
	factorial();
	long long p = fac[n];
	long long s = solve(0, 0);
	long long g = gcd(p, s);
	printf("%lld/%lld", s / g, p / g);
	return 0;
}