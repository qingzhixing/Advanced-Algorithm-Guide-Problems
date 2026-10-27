#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 5;
const int MAX_M = 4;

int n, m;
vector<int> path;

void enumerate(int digit)
{
	if (digit > n)
	{
		for (const auto &item : path)
		{
			cout << item << ' ';
		}
		cout << endl;
		return;
	}

	// 枚举 1 ~ m 尝试填入
	for (int i = 1; i <= m; i++)
	{
		path.push_back(i);
		enumerate(digit + 1);
		path.pop_back();
	}
}

int main()
{
	cin >> n >> m;
	enumerate(1);
	return 0;
}