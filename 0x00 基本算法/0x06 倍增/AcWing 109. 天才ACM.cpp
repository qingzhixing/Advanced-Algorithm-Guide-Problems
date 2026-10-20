#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 5e5 + 10;
const int MAX_M = 1 << 20;

long long a[MAX_N];
// 维护 [L, R) 的排序结果
long long sorted[MAX_N];
long long expanded[MAX_N];
long long tmp[MAX_M];

void solution()
{
	long long n, m, t;
	cin >> n >> m >> t;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	long long result = 0;
	long long L = 0;
	while (L < n)
	{
		// 已确认合法的右端点（开区间）
		long long R = L;
		// 试探增量
		long long step = 1;
		long long sorted_len = 0;

		while (step > 0)
		{
			// 越界
			if (R + step > n)
			{
				step /= 2;
				continue;
			}

			long long expanded_len = step;
			// 新增的试探部分 [R, R + p)
			for (int i = 0; i < expanded_len; i++)
			{
				expanded[i] = a[R + i];
			}
			sort(expanded, expanded + expanded_len);

			// 合并两段，得到候选的 [L, R + p)
			long long total_len = sorted_len + expanded_len;
			long long tmp_len = 0;
			long long expanded_idx = 0, sorted_idx = 0;
			while (tmp_len < total_len)
			{
				if (sorted_idx >= sorted_len || expanded_idx < expanded_len && expanded[expanded_idx] <= sorted[sorted_idx])
				{
					tmp[tmp_len++] = expanded[expanded_idx++];
				}
				else
				{
					tmp[tmp_len++] = sorted[sorted_idx++];
				}
			}

			// 求校验值
			long long verification = 0;
			for (int i = 0; i < min(m, total_len / 2); i++)
			{
				long long delta = tmp[total_len - 1 - i] - tmp[i];
				verification += delta * delta;
				// 剪枝
				if (verification > t)
				{
					break;
				}
			}

			if (verification <= t)
			{
				// 扩展 R，真正更新 sorted，增量 step 翻倍
				R += step;
				step *= 2;
				sorted_len = tmp_len;
				for (int i = 0; i < sorted_len; i++)
				{
					sorted[i] = tmp[i];
				}
			}
			else
			{
				step /= 2;
			}
		}
		L = R;
		result++;
	}

	cout << result << endl;
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		solution();
	}
	return 0;
}