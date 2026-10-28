#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

const int MAX_N = 8;
// 3 ^ 7 <= 3000
const int MAX_M = 3000;

// 当前位置是否要绘制 X
bool graph[MAX_M][MAX_M];

// 当前分形边长大小 以及 当前分形的起始点坐标 (row, col)
void init_graph(int len, pair<int, int> left_up)
{
	const auto &[row, col] = left_up;
	// 最低级的分形
	if (len == 1)
	{
		graph[row][col] = true;
		return;
	}

	/**
	 * @brief 递归枚举
	 * x x
	 *  x
	 * x x
	 */
	const int next_len = len / 3;
	init_graph(next_len, {row, col});								// 左上角
	init_graph(next_len, {row, col + next_len * 2});				// 右上角
	init_graph(next_len, {row + next_len, col + next_len});			// 中间
	init_graph(next_len, {row + next_len * 2, col});				// 左下角
	init_graph(next_len, {row + next_len * 2, col + next_len * 2}); // 右下角
}

int main()
{
	int n = 0;
	cin >> n;
	while (n != -1)
	{
		// 边长
		const int len = pow(3, n - 1);

		memset(graph, 0, sizeof(graph));
		init_graph(len, {0, 0});

		for (int row = 0; row < len; row++)
		{
			for (int col = 0; col < len; col++)
			{
				if (graph[row][col])
				{
					cout << 'X';
				}
				else
				{
					cout << ' ';
				}
			}
			cout << endl;
		}
		cout << '-' << endl;

		// next n
		cin >> n;
	}
	return 0;
}