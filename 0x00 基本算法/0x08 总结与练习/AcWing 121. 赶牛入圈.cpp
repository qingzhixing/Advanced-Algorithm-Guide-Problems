#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 510;
const int MAX_M = 1e4;

typedef long long i64;

int main()
{
	i64 n{}, c{};
	cin >> c >> n;
	vector<pair<i64, i64>> coords;
	// 0 哨兵，防止 idx = -1
	vector<i64> coord_values = {0};
	for (int i = 0; i < n; i++)
	{
		i64 x{}, y{};
		cin >> x >> y;
		coords.push_back({x, y});
		coord_values.push_back(x);
		coord_values.push_back(y);
	}

	// 离散化坐标
	sort(coord_values.begin(), coord_values.end());
	coord_values.erase(unique(coord_values.begin(), coord_values.end()), coord_values.end());
	auto value_cnt = coord_values.size();

	// 1 - indexed
	auto graph = vector<vector<i64>>(value_cnt + 10, vector<i64>(value_cnt + 10));
	// 插入点
	for (const auto &[x, y] : coords)
	{
		// 1 - indexed
		auto target_x = lower_bound(coord_values.begin(), coord_values.end(), x) - coord_values.begin();
		auto target_y = lower_bound(coord_values.begin(), coord_values.end(), y) - coord_values.begin();
		graph[target_x][target_y]++;
	}

	// 在原图上建立二维前缀和
	for (int row = 1; row < value_cnt; row++)
	{
		for (int col = 1; col < value_cnt; col++)
		{
			graph[row][col] += graph[row - 1][col] + graph[row][col - 1] - graph[row - 1][col - 1];
		}
	}

	// 二分搜索最小边长
	auto check = [&](i64 size)
	{
		for (int x1 = 0, x2 = 1; x2 < value_cnt; x2++)
		{
			// 窗口真实覆盖宽度 = coord_values[x2] - coord_values[x1 + 1] + 1
			while (coord_values[x2] - coord_values[x1 + 1] + 1 > size)
			{
				x1++;
			}

			for (int y1 = 0, y2 = 1; y2 < value_cnt; y2++)
			{
				while (coord_values[y2] - coord_values[y1 + 1] + 1 > size)
				{
					y1++;
				}

				i64 current = graph[x2][y2] - graph[x1][y2] - graph[x2][y1] + graph[x1][y1];

				if (current >= c)
				{
					return true;
				}
			}
		}
		return false;
	};

	i64 l = 1, r = MAX_M + 10;
	while (l < r)
	{
		auto mid = (l + r) >> 1;
		if (check(mid))
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}

	cout << l << endl;
	return 0;
}