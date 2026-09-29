#include <iostream>
using namespace std;

long long quick_power(long long base, long long power, long long mod)
{
	base %= mod;
	auto result = 1LL;
	while (power)
	{
		if (power & 1)
		{
			result = (result * base) % mod;
		}
		power >>= 1;
		base = (base * base) % mod;
	}
	return result % mod;
}

void Solution()
{
	int mod;
	int n;

	cin >> mod >> n;

	long long result = 0;
	while (n--)
	{
		long long base, power;
		cin >> base >> power;
		result = (result + quick_power(base, power, mod)) % mod;
	}

	cout << result << endl;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;
	while (t--)
	{
		Solution();
	}
	return 0;
}