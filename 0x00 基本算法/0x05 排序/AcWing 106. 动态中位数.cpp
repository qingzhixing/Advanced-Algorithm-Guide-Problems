#include <iostream>
#include <queue>
using namespace std;

void solution()
{
	int tid, n;
	cin >> tid >> n;

	cout << tid << ' ' << (n + 1) / 2 << endl;

	// 对顶堆维护中位数
	priority_queue<int> max_heap;
	priority_queue<int, vector<int>, greater<>> min_heap;

	int output_cnt = 0;

	auto output = [&](int x)
	{
		if (output_cnt > 0 && output_cnt % 10 == 0)
			cout << '\n';
		if (output_cnt % 10 != 0)
			cout << ' ';
		cout << x;
		output_cnt++;
	};

	for (int i = 1; i <= n; i++)
	{
		int a;
		cin >> a;

		// 第一个数
		if (min_heap.empty())
		{
			min_heap.push(a);
			output(a);
			continue;
		}

		const auto &mid = min_heap.top();
		if (a < mid)
		{
			max_heap.push(a);
		}
		else
		{
			min_heap.push(a);
		}

		if (min_heap.size() > max_heap.size() + 1)
		{
			max_heap.push(min_heap.top());
			min_heap.pop();
		}
		else if (max_heap.size() > min_heap.size())
		{
			min_heap.push(max_heap.top());
			max_heap.pop();
		}

		if (i % 2 == 1)
		{
			output(min_heap.top());
		}
	}
	cout << endl;
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		solution();
	}
	return 0;
}