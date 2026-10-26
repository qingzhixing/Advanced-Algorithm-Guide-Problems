#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 1100;
const int MAX_M = 1000;

struct Node
{
	int parent = -1;
	// 当前点融合了多少点
	int size = 1;
	long long w = 0;
	// 是否被合并
	bool combined = false;
};

// 找到平均价值最大的 未被合并的 非根节点的 节点编号
int biggest_node_idx(const vector<Node> &nodes, int root)
{
	double biggest_average = -1.0;
	int biggest_idx = -1;
	for (int idx = 0; idx < nodes.size(); idx++)
	{
		const auto &[parent, size, w, combined] = nodes[idx];
		if (combined || idx == root)
		{
			continue;
		}
		const auto average = 1.0 * w / size;
		if (biggest_average < average)
		{
			biggest_average = average;
			biggest_idx = idx;
		}
	}
	return biggest_idx;
}

int main()
{
	int n = 0, root = 0;
	cin >> n >> root;

	// 0 - indexed
	--root;

	int result = 0;
	vector<Node> nodes(n);
	for (int idx = 0; idx < n; idx++)
	{
		cin >> nodes[idx].w;
		// 初始总代价，后续拼接产生的额外代价之后累加
		result += nodes[idx].w;
	}

	// 建树
	for (int idx = 0; idx < n - 1; idx++)
	{
		int u = 0, v = 0;
		cin >> u >> v;

		// 0 - indexed
		--u;
		--v;

		nodes[v].parent = u;
	}

	// 贪心合并 n - 1 次
	for (int idx = 0; idx < n - 1; idx++)
	{
		const int biggest = biggest_node_idx(nodes, root);
		// 将该点放在 parent 后面，即与 parent 合并
		int parent = nodes[biggest].parent;

		// 额外代价
		result += nodes[biggest].w * nodes[parent].size;

		nodes[biggest].combined = true;

		// biggest 子节点接到 biggest 父节点身上
		for (int idx = 0; idx < n; idx++)
		{
			if (nodes[idx].parent == biggest)
			{
				nodes[idx].parent = parent;
			}
		}

		// 更新父节点属性
		nodes[parent].w += nodes[biggest].w;
		nodes[parent].size += nodes[biggest].size;
	}

	cout << result << endl;
	return 0;
}