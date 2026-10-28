#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <random>
#include <chrono>
using namespace std;

const int MAX_N = 2e5 + 10;
const int MAX_M = 1e9;
const double INF = 1e18;

struct Point
{
	double x = 0, y = 0;
	int type = 0; // 0: 核电站, 1: 特工
	bool operator<(const Point &other)
	{
		return x < other.x;
	}
};

double dist(const Point &a, const Point &b)
{
	// 相同类型之间距离为 INF
	if (a.type == b.type)
	{
		return INF;
	}
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

Point points[MAX_N];
Point tmp[MAX_N];

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// 分治求解 [l, r] 之间点的最短距离
double division(int l, int r)
{
	// 区间不合法
	if (l >= r)
	{
		return INF;
	}

	// 选取一条中轴线
	int mid = (l + r) >> 1;
	double mid_x = points[mid].x;

	// 递归求左右子区间最小值
	double best = min(division(l, mid), division(mid + 1, r));

	// best 已达到理论最小
	if (best == 0)
	{
		return 0;
	}

	// 现在我们考虑跨区间匹配的部分
	// 归并：把 points[l..r] 按 y 升序整理
	{
		int i = l, j = mid + 1, k = 0;
		while (k < r - l + 1)
		{
			if (j > r || i <= mid && points[i].y <= points[j].y)
			{
				tmp[k++] = points[i++];
			}
			else
			{
				tmp[k++] = points[j++];
			}
		}

		// 拷贝回 points
		for (int t = 0; t < k; ++t)
		{
			points[l + t] = tmp[t];
		}
	}

	// 筛选 x 在 [mid_x - best, mid_x + best] 的点
	int strip_size = 0;
	for (int i = l; i <= r; i++)
	{
		const auto x = points[i].x;
		if (x >= mid_x - best && x <= mid_x + best)
		{
			tmp[strip_size++] = points[i];
		}
	}

	// 在条带内选择 y 的差 <= best 的对
	for (int i = 0; i < strip_size; i++)
	{
		// 枚举前面的点，距离不超过best
		for (int j = i - 1; j >= 0 && tmp[i].y - tmp[j].y <= best; j--)
		{
			best = min(best, dist(tmp[i], tmp[j]));
		}
	}

	return best;
}

void solution()
{
	int n{};
	cin >> n;

	// 核电站
	for (int i = 0; i < n; i++)
	{
		double x{}, y{};
		cin >> x >> y;
		points[i] = {x, y, 0};
	}

	// 特工
	for (int i = n; i < 2 * n; i++)
	{
		double x{}, y{};
		cin >> x >> y;
		points[i] = {x, y, 1};
	}

	// 按 x 排序 points
	shuffle(points, points + 2 * n, rng);
	sort(points, points + 2 * n);

	// 分治求解最短距离
	printf("%.3f\n", division(0, 2 * n - 1));
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