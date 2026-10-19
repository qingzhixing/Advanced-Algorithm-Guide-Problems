#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 5e5 + 10;
const int MAX_M = 1e9;

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
	vector<int> temp(r - l + 1);
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
		if (n == 0)
		{
			return 0;
		}

		reverse_pair_cnt = 0;

		a = vector<int>(n);
		for (auto &item : a)
		{
			cin >> item;
		}

		merge_sort(a, 0, n - 1);

		cout << reverse_pair_cnt << endl;
	}
	return 0;
}