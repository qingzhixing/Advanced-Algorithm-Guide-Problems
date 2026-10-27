#include <iostream>
#include <vector>
#include <string>
using namespace std;

void flip_one(vector<int> &data, int row, int col)
{
	data[row * 4 + col] ^= 1;
}

void operation(vector<int> &data, int row, int col)
{
	for (int i = 0; i < 4; i++)
	{
		flip_one(data, row, i);
		flip_one(data, i, col);
	}
	// 这一点被重复翻转，需要额外再翻转一次
	flip_one(data, row, col);
}

int main()
{
	string s[4];
	vector<int> data;
	for (int i = 0; i < 4; i++)
	{
		cin >> s[i];
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			const char &ch = s[i][j];
			data.push_back(ch == '-');
		}
	}

	// 枚举所有选法
	int min_op = 1e9;
	int min_state = 0;
	for (int state = 0; state < (1 << 16); state++)
	{
		vector<int> backup = data;
		int op = 0;
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				if ((state >> (row * 4 + col)) & 1)
				{
					op++;
					operation(backup, row, col);
				}
			}
		}

		bool valid = true;
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				// 不合法则进入下一次枚举
				if (!backup[row * 4 + col])
				{
					valid = false;
					goto after_check;
				}
			}
		}

	after_check:
		if (!valid)
		{
			continue;
		}

		// 合法则更新最优
		if (op < min_op)
		{
			min_op = op;
			min_state = state;
		}
	}

	cout << min_op << endl;
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if ((min_state >> (row * 4 + col)) & 1)
			{
				cout << row + 1 << ' ' << col + 1 << endl;
			}
		}
	}
	return 0;
}