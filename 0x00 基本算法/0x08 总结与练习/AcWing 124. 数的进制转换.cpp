#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// By Gemini.

using namespace std;

// 字符转数值
int charToVal(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 10;
	return c - 'a' + 36;
}

// 数值转字符
char valToChar(int v)
{
	if (v >= 0 && v <= 9)
		return '0' + v;
	if (v >= 10 && v <= 35)
		return 'A' + (v - 10);
	return 'a' + (v - 36);
}

void solve()
{
	int a{}, b{};
	string s;
	cin >> a >> b >> s;

	// 将输入字符串转为数值数组（为方便去除前导零，这里倒序存储：低位在0，高位在末尾）
	vector<int> num;
	for (int i = (int)s.size() - 1; i >= 0; --i)
	{
		num.push_back(charToVal(s[i]));
	}
	// 去除输入可能自带的前导零
	while (num.size() > 1 && num.back() == 0)
	{
		num.pop_back();
	}

	string res;
	// 特判 0
	if (num.size() == 1 && num[0] == 0)
	{
		res = "0";
	}
	else
	{
		// 模拟短除法：每次将 a 进制大数除以 b
		while (!num.empty() && !(num.size() == 1 && num[0] == 0))
		{
			int r = 0;
			// 从最高位向最低位做除法
			for (int i = (int)num.size() - 1; i >= 0; --i)
			{
				r = r * a + num[i];
				num[i] = r / b;
				r %= b;
			}
			res.push_back(valToChar(r));
			// 去除商的高位前导零
			while (!num.empty() && num.back() == 0)
			{
				num.pop_back();
			}
		}
		// 短除法先得出的是低位，需要翻转得到正常顺序
		reverse(res.begin(), res.end());
	}

	// 按要求格式输出三行
	cout << a << " " << s << "\n";
	cout << b << " " << res << "\n\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T{};
	if (cin >> T)
	{
		while (T--)
		{
			solve();
		}
	}
	return 0;
}