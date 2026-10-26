#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAX_N = 1e3 + 10;
const int MAX_M = 1000;
const int INF = MAX_M + 1000;

int main()
{
	int n = 0, d = 0;
	cin >> n >> d;

	// start, end
	vector<pair<double, double>> ranges;
	for (int i = 1; i <= n; i++)
	{
		double x = 0, y = 0;
		cin >> x >> y;

		if (y > d)
		{
			cout << -1 << endl;
			return 0;
		}

		double delta = sqrt(d * d - y * y);
		ranges.emplace_back(x - delta, x + delta);
	}

	sort(ranges.begin(), ranges.end());

	int result = 0;
	double last_pos = -INF;
	for (const auto &[l, r] : ranges)
	{
		if (l > last_pos)
		{
			result++;
			last_pos = r;
		}
		else
		{
			last_pos = min(r, last_pos);
		}
	}

	cout << result << endl;
	return 0;
}