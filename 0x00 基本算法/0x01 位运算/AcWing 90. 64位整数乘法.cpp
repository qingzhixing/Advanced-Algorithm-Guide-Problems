#include <iostream>
using namespace std;

long long mul_mod(long long a, long long b, long long mod)
{
	long long result = 0;
	while (b)
	{
		if (b & 1)
		{
			result = (result + a) % mod;
		}
		b >>= 1;
		a = (a * 2) % mod;
	}
	return result;
}

int main()
{
	long long a, b, mod;
	cin >> a >> b >> mod;
	cout << mul_mod(a, b, mod) << endl;
	return 0;
}