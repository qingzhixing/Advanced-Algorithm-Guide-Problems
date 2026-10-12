#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 5e7 + 10;
const int MOD = 9901;

// factor, cnt
vector<pair<int, int>> get_factors(int number)
{
	if (number < 2)
	{
		return {};
	}

	vector<pair<int, int>> factors;
	for (int i = 2; i <= number / i; i++)
	{
		if (number % i == 0)
		{
			int cnt = 0;
			while (number % i == 0)
			{
				number /= i;
				cnt++;
			}
			factors.push_back({i, cnt});
		}
	}
	if (number > 1)
	{
		factors.push_back({number, 1});
	}
	return factors;
}

int quick_power(int base, long long power, int mod)
{
	base %= mod;

	int result = 1;
	while (power)
	{
		if (power & 1)
		{
			result = result * base % mod;
		}
		base = base * base % mod;
		power >>= 1;
	}

	return result;
}

// 求 1 + p ^ 1 + ... + p ^ c
int sum(int p, long long c, int mod)
{
	if (c == 0)
	{
		return 1;
	}

	p %= mod;

	// p - 1 逆元不存在
	if (p == 1)
	{
		// 每一个 p ^ i (i in [0, c]) % mod = 1
		// 其和 % mod = 1 * (c + 1) % mod
		return (c + 1) % mod;
	}

	// 费马小定理求模逆元
	const auto mod_inverse = quick_power(p - 1, mod - 2, mod);

	return (quick_power(p, c + 1, mod) - 1) * (mod_inverse) % mod;
}

int main()
{
	int base;
	long long power;

	cin >> base >> power;

	if (base == 0)
	{
		cout << 0 << endl;
		return 0;
	}

	const auto factors = get_factors(base);

	int result = 1;

	for (const auto &[factor, cnt] : factors)
	{
		result = result * sum(factor, cnt * power, MOD) % MOD;
	}

	cout << result << endl;
	return 0;
}