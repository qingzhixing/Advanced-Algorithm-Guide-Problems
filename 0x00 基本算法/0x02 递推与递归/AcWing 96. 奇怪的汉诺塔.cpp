#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	// 3 塔模式下的汉诺塔方案数
	int d[13];
	// 4 塔模式下的汉诺塔方案数
	int f[13];

	memset(f, 0x3f, sizeof(f));
	d[1] = 1;
	f[1] = 1;

	// 求 d
	for (int i = 2; i <= 12; i++)
	{
		d[i] = 2 * d[i - 1] + 1;
	}

	// 求 f
	for (int i = 2; i <= 12; i++)
	{
		// 枚举分割点
		for (int j = 0; j < i; j++)
		{
			f[i] = min(f[i], 2 * f[j] + d[i - j]);
		}
	}

	for (int i = 1; i <= 12; i++)
	{
		cout << f[i] << endl;
	}
	return 0;
}