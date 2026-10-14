#include <iostream>
using namespace std;

const int MAX_N = 1e5 + 10;
const int MAX_M = 2e3;
const int INF = MAX_N * MAX_M;
const double eps = 1e-5;

int n, f;
double a[MAX_N];
// b[i] = a[i] - average
double b[MAX_N];
// b 的前缀和
double prefix_sum[MAX_N];

bool verify(double average)
{
	for (int i = 1; i <= n; i++)
	{
		b[i] = a[i] - average;
		prefix_sum[i] = prefix_sum[i - 1] + b[i];
	}

	double max_subsequence = -INF;
	// 前缀最小的 prefix_sum[i]
	double min_prefix = INF;

	for (int i = f; i <= n; i++)
	{
		min_prefix = min(min_prefix, prefix_sum[i - f]);
		max_subsequence = max(max_subsequence, prefix_sum[i] - min_prefix);
	}

	// 最大子段和 >= 0 表明存在一个长度 >= f 的区间，平均数 >= average
	return max_subsequence >= 0;
}

int main()
{
	cin >> n >> f;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}

	double l = -INF, r = INF;
	while (r - l > eps)
	{
		double mid = (l + r) / 2;
		if (verify(mid))
		{
			l = mid;
		}
		else
		{
			r = mid;
		}
	}

	printf("%d\n", (int)(r * 1000));

	return 0;
}