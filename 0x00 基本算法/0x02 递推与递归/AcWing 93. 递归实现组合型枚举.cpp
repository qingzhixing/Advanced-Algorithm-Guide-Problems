#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> chosen;

// 枚举到数字 x 了
void enumerate(int x)
{
	// 若选超过了，或者后面全选也达不到 m 个，直接剪枝
	if (chosen.size() > m || chosen.size() + (n - x + 1) < m)
	{
		return;
	}

	if (x > n)
	{
		for (const auto &item : chosen)
		{
			cout << item << ' ';
		}
		cout << endl;
		return;
	}

	// 选 x
	chosen.push_back(x);
	enumerate(x + 1);
	chosen.pop_back();

	// 不选 x
	enumerate(x + 1);
}

int main()
{
	cin >> n >> m;
	enumerate(1);
	return 0;
}