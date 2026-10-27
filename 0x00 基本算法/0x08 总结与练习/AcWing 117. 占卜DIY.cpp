#include <iostream>
#include <queue>
#include <map>
using namespace std;

struct Card
{
	int value;
	bool up;
};

int char_idx(char ch)
{
	int result = 0;
	switch (ch)
	{
	case 'A':
	{
		result = 1;
		break;
	}
	case '0':
	{
		result = 10;
		break;
	}
	case 'J':
	{
		result = 11;
		break;
	}
	case 'Q':
	{
		result = 12;
		break;
	}
	case 'K':
	{
		result = 13;
		break;
	}

	default:
	{
		result = ch - '0';
		break;
	}
	}
	return result;
}

int main()
{
	deque<Card> cards[14];
	for (int i = 1; i <= 13; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			char ch = 0;
			cin >> ch;
			cards[i].push_back({char_idx(ch), false});
		}
	}

	map<int, int> freq;
	int death = 0;
	while (death < 4)
	{
		auto [value, _up] = cards[13].front();
		cards[13].pop_front();

		while (value != 13)
		{
			// 把当前牌放到对应数字堆的顶部
			cards[value].push_front({value, true});

			// 抽新的卡
			auto [nxt, _up] = cards[value].back();
			cards[value].pop_back();
			value = nxt;
		}
		death++;
	}

	int result = 0;
	for (int i = 1; i <= 13; i++)
	{
		for (const auto &[value, up] : cards[i])
		{
			if (up)
			{
				freq[value]++;
				if (freq[value] >= 4)
				{
					result++;
				}
			}
		}
	}
	cout << result << endl;
	return 0;
}