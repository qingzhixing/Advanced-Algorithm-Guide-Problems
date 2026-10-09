#include <iostream>
#include <cstring>
using namespace std;

const int MAX_N = 21;
const int MAX_M = 1 << MAX_N;

int n;
int a[MAX_N][MAX_N];
// dp[i][j] = 所有以 j 为终点，途径点状态为 i 的路径的最小值
int dp[MAX_M][MAX_N];

int main()
{
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> a[i][j];
		}
	}

	memset(dp, 0x3f, sizeof(dp));

	// 0 to 0 = 0
	dp[1][0] = 0;

	// 枚举状态 i
	for (int state = 0; state < (1 << n); state++)
	{
		// 枚举终点 j
		for (int end = 0; end < n; end++)
		{
			// 当前状态不合法
			if (((state >> end) & 1) == 0)
			{
				continue;
			}

			const auto previous_state = state - (1 << end);

			// 枚举倒数第二个点
			for (int previous = 0; previous < n; previous++)
			{
				// 前一个状态不合法
				if (((previous_state >> previous) & 1) == 0)
				{
					continue;
				}
				dp[state][end] = min(dp[state][end], dp[previous_state][previous] + a[previous][end]);
			}
		}
	}

	cout << dp[(1 << n) - 1][n - 1] << endl;

	return 0;
}