#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 110;
const int MAX_M = 128;

int main()
{
	int n{};
	cin >> n;

	vector<vector<int>> a(n + 10, vector<int>(n + 10));

	// 记录每一列的前缀和
	vector<vector<int>> s(n + 10, vector<int>(n + 10));

	for (int row = 1; row <= n; row++)
	{
		for (int column = 1; column <= n; column++)
		{
			cin >> a[row][column];
			s[row][column] += s[row - 1][column] + a[row][column];
		}
	}

	int result = -2e10;
	// 枚举两个行号，将其中间矩阵压缩至一位数组
	// 所有这样的一维数组的最大子序列和的最大值
	//  即为 n * n 矩阵的最大子矩阵
	for (int start_row = 1; start_row <= n; start_row++)
	{
		for (int end_row = start_row; end_row <= n; end_row++)
		{
			// 求最大子序列
			// 以当前点为末端点的最大子序列
			int subsequence = 0;
			for (int column = 1; column <= n; column++)
			{
				subsequence += s[end_row][column] - s[start_row - 1][column];
				result = max(result, subsequence);

				// 如果当前子段和小于零，则在下一次迭代前丢弃前面部分
				subsequence = max(0, subsequence);
			}
		}
	}

	cout << result << endl;
	return 0;
}