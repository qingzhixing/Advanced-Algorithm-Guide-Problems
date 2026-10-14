#include <vector>
using namespace std;

// return bool means whether a is less than b.
bool compare(int a, int b);

// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.

class Solution
{
public:
	vector<int> specialSort(int N)
	{
		vector<int> result;

		for (int i = 1; i <= N; i++)
		{
			if (result.empty())
			{
				result.push_back(i);
				continue;
			}

			// 二分查找合法位置
			int l = 0, r = result.size();
			while (l < r)
			{
				int mid = (l + r) >> 1;
				if (compare(i, result[mid]))
				{
					// mid 及其左边一定存在一个合法位置
					r = mid;
				}
				else
				{
					// mid 右侧一定有合法位置
					l = mid + 1;
				}
			}
			result.insert(result.begin() + l, i);
		}
		return result;
	}
};