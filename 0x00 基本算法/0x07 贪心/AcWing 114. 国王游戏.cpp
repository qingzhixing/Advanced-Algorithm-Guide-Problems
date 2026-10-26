#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_N = 1100;
const int MAX_M = 1e4;

vector<int> mul(vector<int> &A, int b) // C = A * b, A >= 0, b >= 0
{
	vector<int> C;

	int t = 0;
	for (int i = 0; i < A.size() || t; i++)
	{
		if (i < A.size())
			t += A[i] * b;
		C.push_back(t % 10);
		t /= 10;
	}

	while (C.size() > 1 && C.back() == 0)
		C.pop_back();

	return C;
}

vector<int> div(vector<int> &A, int b, int &r) // A / b = C ... r, A >= 0, b > 0
{
	vector<int> C;
	r = 0;
	for (int i = A.size() - 1; i >= 0; i--)
	{
		r = r * 10 + A[i];
		C.push_back(r / b);
		r %= b;
	}
	reverse(C.begin(), C.end());
	while (C.size() > 1 && C.back() == 0)
		C.pop_back();
	return C;
}

vector<int> max_vec(vector<int> a, vector<int> b)
{
	if (a.size() > b.size())
		return a;
	if (a.size() < b.size())
		return b;
	if (vector<int>(a.rbegin(), a.rend()) > vector<int>(b.rbegin(), b.rend()))
		return a;
	return b;
}

int main()
{
	int n = 0;
	cin >> n;
	typedef pair<int, int> Hand;
	Hand king = {0, 0};
	cin >> king.first >> king.second;

	vector<Hand> ministers;
	while (n--)
	{
		Hand minister;
		cin >> minister.first >> minister.second;
		ministers.emplace_back(move(minister));
	}

	// 按照左右手乘积排序
	sort(ministers.begin(), ministers.end(), [](const auto &a, const auto &b)
		 { return a.first * a.second < b.first * b.second; });

	vector<int> max_gold = {0};
	// 前面的人左手价值累乘器
	vector<int> acc = {king.first};
	for (const auto &[l, r] : ministers)
	{
		int _remainder = 0;
		max_gold = max_vec(max_gold, div(acc, r, _remainder));
		acc = mul(acc, l);
	}

	reverse(max_gold.begin(), max_gold.end());
	for (const auto &digit : max_gold)
	{
		cout << digit;
	}
	cout << endl;
	return 0;
}