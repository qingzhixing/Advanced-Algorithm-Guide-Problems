#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 3e3;
const int MAX_M = 1e3;

int main()
{
	int n, m;
	cin >> n >> m;
	// min, max
	vector<pair<int, int>> spf_needs(n);
	// spf, cnt
	vector<pair<int, int>> suncreams(m);

	for (auto &[min_spf, max_spf] : spf_needs)
	{
		cin >> min_spf >> max_spf;
	}
	for (auto &[spf, cnt] : suncreams)
	{
		cin >> spf >> cnt;
	}

	sort(spf_needs.begin(), spf_needs.end(), [](auto &a, auto &b)
		 { return b < a; });

	int result = 0;
	for (auto &[min_spf, max_spf] : spf_needs)
	{
		pair<int, int> *best_suncreams = nullptr;
		for (int i = 0; i < m; i++)
		{
			auto &[spf, cnt] = suncreams[i];
			if (spf >= min_spf && spf <= max_spf && cnt > 0)
			{
				if (best_suncreams == nullptr || best_suncreams->first < spf)
				{
					best_suncreams = &suncreams[i];
				}
			}
		}
		if (best_suncreams != nullptr)
		{
			result++;
			best_suncreams->second--;
		}
	}
	cout << result << endl;
	return 0;
}