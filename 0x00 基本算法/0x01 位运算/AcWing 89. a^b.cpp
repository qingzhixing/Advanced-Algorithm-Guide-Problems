#include <iostream>
using namespace std;

int quick_power(int base, int power, int mod)
{
	base %= mod;
	auto result = 1;
	while (power)
	{
		if (power & 1)
		{
			result = (1LL * result * base) % mod;
		}
		power >>= 1;
		base = (1LL * base * base) % mod;
	}
	return result % mod;
}

int main()
{
	int base, power, mod;
	cin >> base >> power >> mod;
	cout << quick_power(base, power, mod) << endl;
	return 0;
}