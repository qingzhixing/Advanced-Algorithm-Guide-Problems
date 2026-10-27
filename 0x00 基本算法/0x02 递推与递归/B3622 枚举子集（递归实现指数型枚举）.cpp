#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 12;

int n;
vector<bool> path;

void enumerate(int digit)
{
	if (digit > n)
	{
		for (const auto &choosed : path)
		{
			cout << (choosed ? "Y" : "N");
		}
		cout << endl;
		return;
	}

	// 不选
	path.push_back(false);
	enumerate(digit + 1);

	path.pop_back();

	// 选
	path.push_back(true);
	enumerate(digit + 1);

	path.pop_back();
}

int main()
{
	cin>>n;
	enumerate(1);
	return 0;
}