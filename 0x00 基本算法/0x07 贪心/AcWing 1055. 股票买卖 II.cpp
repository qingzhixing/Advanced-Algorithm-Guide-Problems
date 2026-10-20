#include <iostream>
using namespace std;

const int MAX_N = 1e5 + 10;
const int MAX_M = 1e4;

int main()
{
	int n;
	cin >> n;

	int last_number = 0;
	int result = 0;

	for (int i = 1; i <= n; i++)
	{
		int number;
		cin >> number;
		if (i >= 2 && number > last_number)
		{
			result += number - last_number;
		}
		last_number = number;
	}

	cout << result << endl;
	return 0;
}