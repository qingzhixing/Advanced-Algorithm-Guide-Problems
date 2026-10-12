#include <iostream>
#include <cmath>
using namespace std;

const int MAX_N = 32;
const int MAX_M = 2e10;

// 返回 n 级城市下编号为 m 的房屋所在的点的 (row, column)
pair<long long, long long> get_coord(int n, long long m)
{
	if (n == 0)
	{
		return {0, 0};
	}

	// 次级市区边长 = 2 ^ (n-1)
	const auto sub_len = 1LL << (n - 1);
	// 次级市区房屋数量 = 4 ^ (n - 1) = 2 ^ (2 * n - 2)
	const auto sub_amount = 1LL << (2 * n - 2);

	// 求当前房屋在下一级市区的那个位置
	const auto &[sub_row, sub_column] = get_coord(n - 1, m % sub_amount);

	// 当前房屋在哪一个子市区 (象限)
	const auto quadrant = m / sub_amount;
	switch (quadrant)
	{
	case 0:
	{
		// 顺时针旋转 + 水平翻转
		return {sub_column, sub_row};
		break;
	}
	case 1:
	{
		// 仅平移
		return {sub_row, sub_column + sub_len};
		break;
	}
	case 2:
	{
		// 仅平移
		return {sub_row + sub_len, sub_column + sub_len};
		break;
	}
	case 3:
	{
		// 逆时针旋转 + 水平翻转
		return {2 * sub_len - sub_column - 1, sub_len - sub_row - 1};
		break;
	}
	}

	return {0, 0};
}

void solution()
{
	int n;
	long long a, b;
	cin >> n >> a >> b;

	// 0 - indexed
	--a;
	--b;

	const auto &[row_a, column_a] = get_coord(n, a);
	const auto &[row_b, column_b] = get_coord(n, b);
	const auto d_row = 1. * row_a - row_b;
	const auto d_column = 1. * column_a - column_b;
	printf("%.0f\n", 10 * sqrt(d_row * d_row + d_column * d_column));
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