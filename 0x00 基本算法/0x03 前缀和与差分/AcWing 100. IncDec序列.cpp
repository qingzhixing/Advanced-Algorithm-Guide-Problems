#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int MAX_N = 1e5 + 10;
const int MAX_M = INT_MAX;

int main()
{
	int n;
	cin >> n;

	vector<int> a(n + 10);
	vector<int> diff(n + 10);

	long long negative = 0, positive = 0;

	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];

		if (i < 2)
		{
			continue;
		}

		// 求差分数组
		diff[i] = a[i] - a[i - 1];

		if (diff[i] > 0)
		{
			positive += diff[i];
		}
		else if (diff[i] < 0)
		{
			negative += abs(diff[i]);
		}
	}

	// 操作次数
	cout << max(negative, positive) << endl;

	// 产生的结果数
	cout << abs(negative - positive) + 1 << endl;

	return 0;
}