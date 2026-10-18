#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 1e5 + 10;
const int MAX_M = 1e5;

int main()
{
	// n 行 m 列
	int n, m, t;
	cin >> n >> m >> t;
	vector<long long> row_favor(n + 10);
	vector<long long> col_favor(m + 10);
	for (int i = 1; i <= t; i++)
	{
		int row, col;
		cin >> row >> col;
		row_favor[row]++;
		col_favor[col]++;
	}

	bool row_possible = true;
	bool col_possible = true;
	if (t % m != 0)
	{
		col_possible = false;
	}
	if (t % n != 0)
	{
		row_possible = false;
	}

	if (!col_possible && !row_possible)
	{
		cout << "impossible" << endl;
		return 0;
	}

	if (!col_possible)
	{
		cout << "row ";
	}
	else if (!row_possible)
	{
		cout << "column ";
	}
	else
	{
		cout << "both ";
	}

	// 计算前缀和
	vector<long long> presum_row(n + 10);
	vector<long long> presum_col(m + 10);

	for (int i = 1; i <= n; i++)
	{
		row_favor[i] -= t / n;
		presum_row[i] = presum_row[i - 1] + row_favor[i];
	}

	for (int i = 1; i <= m; i++)
	{
		col_favor[i] -= t / m;
		presum_col[i] = presum_col[i - 1] + col_favor[i];
	}

	long long result = 0;
	// 统计每一行均分的代价
	if (row_possible)
	{
		sort(presum_row.begin() + 1, presum_row.begin() + 1 + n);
		long long seperate_presum;
		if (n % 2 == 0)
		{
			seperate_presum = presum_row[n / 2];
		}
		else
		{
			seperate_presum = presum_row[(n + 1) / 2];
		}
		for (int i = 1; i <= n; i++)
		{
			const auto &presum = presum_row[i];
			result += abs(presum - seperate_presum);
		}
	}

	// 统计每一列均分的代价
	if (col_possible)
	{
		sort(presum_col.begin() + 1, presum_col.begin() + 1 + m);
		long long seperate_presum;
		if (m % 2 == 0)
		{
			seperate_presum = presum_col[m / 2];
		}
		else
		{
			seperate_presum = presum_col[(m + 1) / 2];
		}
		for (int i = 1; i <= m; i++)
		{
			const auto &presum = presum_col[i];
			result += abs(presum - seperate_presum);
		}
	}

	cout << result << endl;
	return 0;
}