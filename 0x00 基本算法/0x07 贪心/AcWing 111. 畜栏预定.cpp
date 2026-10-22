#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX_N = 5e4 + 10;
const int MAX_M = 1e6;

int main()
{
	int n;
	cin >> n;

	// start, end, id
	vector<tuple<int, int, int>> cows(n);
	for (int i = 1; i <= n; i++)
	{
		auto &[start, end, id] = cows[i - 1];
		cin >> start >> end;
		id = i;
	}

	sort(cows.begin(), cows.end());

	// 当前奶牛对应的畜栏
	vector<int> corrals(n + 1);

	// 小根堆存每个畜栏最右边点的坐标 和 队列编号
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> rightest;
	int list_cnt = 0;
	for (const auto &[start, end, id] : cows)
	{
		if (rightest.empty())
		{
			// 新开一个队列
			list_cnt++;
			rightest.push({end, list_cnt});
			corrals[id] = list_cnt;
			continue;
		}

		auto [min_right, idx] = rightest.top();
		if (start > min_right)
		{
			// 将其插入 min_right 对应队列
			rightest.pop();
			rightest.push({end, idx});
			corrals[id] = idx;
		}
		else
		{
			// 新开一个队列
			list_cnt++;
			rightest.push({end, list_cnt});
			corrals[id] = list_cnt;
		}
	}

	cout << list_cnt << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << corrals[i] << endl;
	}
	return 0;
}