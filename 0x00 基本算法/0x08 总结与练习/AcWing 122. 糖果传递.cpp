#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 1e6 + 10;
const int MAX_M = 2e9;

typedef long long i64;

int main()
{
	i64 n{};
	cin >> n;
	// 1 - indexed
	vector<i64> nums(n + 1);
	i64 sum{};
	for (int i = 1; i <= n; i++)
	{
		cin >> nums[i];
		sum += nums[i];
	}

	const i64 average = sum / n;

	// 差值前缀和
	vector<i64> delta_presum(n + 1);
	for (int i = 1; i <= n; i++)
	{
		delta_presum[i] = delta_presum[i - 1] + nums[i] - average;
	}

	sort(delta_presum.begin() + 1, delta_presum.end());
	const auto mid = delta_presum[n / 2 + 1];

	i64 result{};
	for (int i = 1; i <= n; i++)
	{
		result += abs(delta_presum[i] - mid);
	}

	cout << result << endl;
	return 0;
}