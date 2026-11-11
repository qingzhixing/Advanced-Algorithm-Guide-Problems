#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long i64;

int main()
{
	i64 n{};
	cin >> n;
	vector<pair<i64, i64>> cows;
	for (int i = 1; i <= n; i++)
	{
		i64 w{};
		i64 s{};
		cin >> w >> s;
		cows.push_back({w, s});
	}
	sort(cows.begin(), cows.end(), [](auto a, auto b)
		 { return (a.first + a.second) < (b.first + b.second); });

	i64 result = -1e14;
	i64 w_sum = 0;
	for (const auto &[w, s] : cows)
	{
		result = max(result, w_sum - s);
		w_sum += w;
	}
	cout << result << endl;
	return 0;
}