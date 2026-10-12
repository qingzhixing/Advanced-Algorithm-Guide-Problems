#include <iostream>
using namespace std;

const int MAX_N = 5e3 + 10;
int n;
int r;
int a[MAX_N][MAX_N];

int main()
{
	cin >> n >> r;

	for (int i = 1; i <= n; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;

		// 1 - indexed
		++x;
		++y;

		a[x][y] += w;
	}

	// 求 a 前缀和
	for (int i = 1; i < MAX_N; i++)
	{
		for (int j = 1; j < MAX_N; j++)
		{
			a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
		}
	}

	int result = 0;
	// 枚举右下角点
	for (int i = MAX_N - 1; i >= 1; i--)
	{
		for (int j = MAX_N - 1; j >= 1; j--)
		{
			int minus_time = 0;
			int current_ans = a[i][j];
			if (i > r)
			{
				current_ans -= a[i - r][j];
				minus_time++;
			}
			if (j > r)
			{
				current_ans -= a[i][j - r];
				minus_time++;
			}

			if (minus_time >= 2)
			{
				current_ans += a[i - r][j - r];
			}

			result = max(result, current_ans);
		}
	}

	cout << result << endl;
	return 0;
}