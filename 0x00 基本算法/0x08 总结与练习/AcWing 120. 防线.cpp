#include <iostream>
#include <vector>
#include <cstdint>
#include <climits>
using namespace std;

const int MAX_N = 2e5 + 10;
const int MAX_M = 1e9;

typedef long long i64;

struct Sequence
{
	i64 start, end, step;
};

void solution()
{
	i64 n{};
	cin >> n;
	vector<Sequence> sequences{};
	for (int i = 0; i < n; i++)
	{
		i64 start{}, end{}, step{};
		cin >> start >> end >> step;
		sequences.push_back({start, end, step});
	}

	// 二分搜索奇数点
	// 判断 <= x 点是否为奇数个
	auto get_prefix_cnt = [&](i64 x) -> i64
	{
		i64 result = 0;
		for (const auto &[start, end, step] : sequences)
		{
			// 当前区间与前缀统计 x 没有交集
			if (start > x)
			{
				continue;
			}

			i64 seq_end = min(end, x);

			result += (seq_end - start) / step + 1;
		}

		return result;
	};

	i64 l = 0, r = INT_MAX;
	while (l < r)
	{
		auto mid = (l + r) >> 1;
		if (get_prefix_cnt(mid) & 1)
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}

	auto point_cnt = get_prefix_cnt(l) - get_prefix_cnt(l - 1);
	if (point_cnt % 2 == 0)
	{
		cout << "There's no weakness." << endl;
		return;
	}
	printf("%lld %lld\n", l, point_cnt);
}

int main()
{
	int t = 0;
	cin >> t;
	while (t--)
	{
		solution();
	}
	return 0;
}