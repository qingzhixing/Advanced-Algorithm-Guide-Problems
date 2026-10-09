#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 10;

int n;
bool selected[MAX_N];
vector<int> result;

// 选到第 idx 个数字
void enumerate(int idx)
{
	if (idx > n)
	{
		for (const auto &item : result)
		{
			cout << item << ' ';
		}
		cout << endl;
		return;
	}

	// 枚举数字尝试放入
	for (int i = 1; i <= n; i++)
	{
		if (!selected[i])
		{
			selected[i] = true;
			result.push_back(i);
			enumerate(idx + 1);
			result.pop_back();
			selected[i] = false;
		}
	}
}

int main()
{
	cin >> n;
	enumerate(1);
	return 0;
}