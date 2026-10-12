#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

const int MAX_N = 510;

const int d_column[4] = {0, 0, -1, 1};
const int d_row[4] = {-1, 1, 0, 0};

void solution()
{
	vector<bitset<5>> a(5);
	for (int i = 0; i < 5; i++)
	{
		string str;
		cin >> str;
		for (int j = 0; j < 5; j++)
		{
			a[i][j] = str[j] - '0';
		}
	}

	const auto tap = [](vector<bitset<5>> &graph, int row, int column)
	{
		if (row < 0 || row > 4 || column < 0 || column > 4)
		{
			return;
		}

		graph[row][column].flip();

		for (int direction = 0; direction < 4; direction++)
		{
			const auto nxt_row = row + d_row[direction];
			const auto nxt_column = column + d_column[direction];
			if (nxt_row < 0 || nxt_row > 4 || nxt_column < 0 || nxt_column > 4)
			{
				continue;
			}
			graph[nxt_row][nxt_column].flip();
		}
	};

	int result = 1e9;
	// 枚举第一行的按动方式
	for (int state = 0; state < (1 << 5); state++)
	{
		vector<bitset<5>> graph(a);
		// 操作次数
		int cnt = 0;
		for (int column = 0; column < 5; column++)
		{
			if ((state >> column) & 1)
			{
				cnt++;
				tap(graph, 0, column);
			}
		}

		// 枚举后面四行的按法: 上一行为 0 就按
		bool failed = false;
		for (int row = 1; row < 5; row++)
		{
			for (int column = 0; column < 5; column++)
			{
				if (graph[row - 1][column] == 0)
				{
					cnt++;
					tap(graph, row, column);
					if (cnt > 6)
					{
						failed = true;
						break;
					}
				}
			}
			if (failed)
			{
				break;
			}
		}

		if (failed)
		{
			continue;
		}

		// 检查最后一行是否全为 1
		for (int column = 0; column < 5; column++)
		{
			if (graph[4][column] == 0)
			{
				failed = true;
				break;
			}
		}
		if (!failed)
		{
			result = min(result, cnt);
		}
	}

	if (result != 1e9)
	{
		cout << result << endl;
	}
	else
	{
		cout << -1 << endl;
	}
}

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		solution();
	}
	return 0;
}