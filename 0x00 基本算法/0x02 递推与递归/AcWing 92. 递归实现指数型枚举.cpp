#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> result;

// 枚举到数字 x 了
void enumerate(int x)
{
	if (x > n)
	{
		for (const auto &item : result)
		{
			cout << item << ' ';
		}
		cout << endl;
		return;
	}

	// 不选 x
	enumerate(x + 1);

	// 选 x
	result.push_back(x);
	enumerate(x + 1);
	result.pop_back();
}

int main()
{
	cin >> n;
	enumerate(1);
	return 0;
}