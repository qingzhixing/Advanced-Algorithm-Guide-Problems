#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX_N = 2e5 + 10;
const int MAX_M = 1e9;

struct Door
{
	// 1 - OR, 2 - XOR, 3 - AND
	int op;
	int t;
};

// 查询在 door 第 idx 位放置 value 会输出的结果
bool apply_doors(const vector<Door> &doors, int idx, bool value)
{
	for (const auto &[op, t] : doors)
	{
		bool digit = (t >> idx) & 1;
		if (op == 1)
		{
			value |= digit;
			continue;
		}
		if (op == 2)
		{
			value ^= digit;
			continue;
		}
		if (op == 3)
		{
			value &= digit;
			continue;
		}
		cout << "Unknown Operator!" << endl;
	}
	return value;
}

int main()
{
	int n, m;
	vector<Door> doors;
	cin >> n >> m;
	while (n--)
	{
		string op;
		int t;
		cin >> op >> t;
		if (op == "OR")
		{
			doors.push_back({1, t});
			continue;
		}
		if (op == "XOR")
		{
			doors.push_back({2, t});
			continue;
		}
		if (op == "AND")
		{
			doors.push_back({3, t});
			continue;
		}
	}

	int result = 0;
	// 按位枚举看应该填什么
	for (int idx = 30; idx >= 0; idx--)
	{
		const auto out0 = apply_doors(doors, idx, 0);
		const auto out1 = apply_doors(doors, idx, 1);

		// 填 1 更优 并且 可填
		if (out1 == 1 && out0 == 0 && m >= (1 << idx))
		{
			m -= (1 << idx);
			result += (out1 << idx);
		}
		else
		{
			// 填 0 更优
			result += (out0 << idx);
		}
	}

	cout << result << endl;
	return 0;
}