#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int MAX_N = 1e4 + 10;
const int MAX_M = 1e6;

int main()
{
	int n, p, h, m;
	cin >> n >> p >> h >> m;

	vector<int> diff(n + 10);
	vector<int> a(n + 10);
	// {A, B} -> exist
	map<pair<int, int>, bool> exist;

	for (int i = 1; i <= m; i++)
	{
		int a, b;
		cin >> a >> b;
		if (a > b)
		{
			swap(a, b);
		}
		if (exist[{a, b}])
		{
			continue;
		}
		exist[{a, b}] = true;

		// 将 a + 1 ~ b - 1 全部 -1
		diff[a + 1]--;
		diff[b]++;
	}

	// 还原原数组
	for (int i = 1; i <= n; i++)
	{
		a[i] = a[i - 1] + diff[i];
		cout << a[i] + h << endl;
	}
	return 0;
}