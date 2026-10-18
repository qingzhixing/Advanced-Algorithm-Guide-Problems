#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	cin >> n;

	vector<int> a(n);
	for (auto &item : a)
	{
		cin >> item;
	}

	sort(a.begin(), a.end());
	int target = a[n / 2];

	int result = 0;
	for (const auto &item : a)
	{
		result += abs(item - target);
	}

	cout << result << endl;
	return 0;
}