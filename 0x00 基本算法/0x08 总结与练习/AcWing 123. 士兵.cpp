#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 1e4 + 10;
const int MAX_M = 1e4;

typedef long long i64;

int main()
{
	i64 n{};
	cin >> n;
	vector<i64> y_array;
	vector<i64> delta_x_array;
	for (auto i = 0; i < n; i++)
	{
		i64 x{}, y{};
		cin >> x >> y;
		delta_x_array.push_back(x);
		y_array.push_back(y);
	}

	sort(delta_x_array.begin(), delta_x_array.end());
	sort(y_array.begin(), y_array.end());

	for (auto i = 0; i < n; i++)
	{
		delta_x_array[i] -= i;
	}

	sort(delta_x_array.begin(), delta_x_array.end());

	auto target_y = y_array[n / 2];
	auto target_x = delta_x_array[n / 2];
	i64 result = {};
	for (auto i = 0; i < n; i++)
	{
		result += abs(y_array[i] - target_y) + abs(delta_x_array[i] - target_x);
	}
	cout << result << endl;
	return 0;
}