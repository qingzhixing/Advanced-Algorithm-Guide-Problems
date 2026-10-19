#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 510;
const int MAX_M = 3e5;

int n;
vector<int> a;
long long reverse_pair_cnt;

void merge_sort(vector<int> &a, int l, int r)
{
	if (l == r)
	{
		return;
	}

	// 分成两个部分
	int mid = (l + r) >> 1;
	merge_sort(a, l, mid);
	merge_sort(a, mid + 1, r);

	// 合并 a[l ~ mid], a[mid + 1 ~ r]
	static vector<int> temp(MAX_M);
	int l_idx = l, r_idx = mid + 1;
	for (int temp_idx = 0; temp_idx < r - l + 1; temp_idx++)
	{
		if (r_idx > r || l_idx <= mid && a[l_idx] <= a[r_idx])
		{
			temp[temp_idx] = a[l_idx++];
		}
		else
		{
			temp[temp_idx] = a[r_idx++];
			// a[l_idx ~ mid] 比 a[r_idx] 都要大
			reverse_pair_cnt += mid - l_idx + 1;
		}
	}

	for (int temp_idx = 0; temp_idx < r - l + 1; temp_idx++)
	{
		a[temp_idx + l] = temp[temp_idx];
	}
}

int main()
{
	while (cin >> n)
	{
		if (n == 1)
		{
			int _1, _2;
			cin >> _1 >> _2;
			cout << "TAK" << endl;
			continue;
		}

		bool odd[2] = {};
		for (int i = 0; i < 2; i++)
		{
			reverse_pair_cnt = 0;
			a.clear();
			a.reserve(n * n - 1);
			for (int j = 1; j <= n * n; j++)
			{
				int item;
				cin >> item;
				if (item != 0)
				{
					a.push_back(item);
				}
			}

			merge_sort(a, 0, n * n - 2);
			odd[i] = reverse_pair_cnt % 2;
		}

		if (odd[0] == odd[1])
		{
			cout << "TAK" << endl;
		}
		else
		{
			cout << "NIE" << endl;
		}
	}

	return 0;
}