#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 2e5 + 10;
const int MAX_M = 1e9;

int n, m;

vector<int> human, voice, caption;
vector<int> all_language;
vector<int> language_cnt;

// all_language 中查询 language 的下标
int query(int language)
{
	return lower_bound(all_language.begin(), all_language.end(), language) - all_language.begin();
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;

	human.reserve(n);
	voice.reserve(n);
	caption.reserve(n);

	all_language.reserve(n + 2 * MAX_N);

	for (int i = 1; i <= n; i++)
	{
		int a;
		cin >> a;
		human.push_back(a);
		all_language.push_back(a);
	}

	cin >> m;

	for (int i = 1; i <= m; i++)
	{
		int b;
		cin >> b;
		voice.push_back(b);
		all_language.push_back(b);
	}
	for (int i = 1; i <= m; i++)
	{
		int c;
		cin >> c;
		caption.push_back(c);
		all_language.push_back(c);
	}

	// 离散化
	sort(all_language.begin(), all_language.end());
	all_language.erase(unique(all_language.begin(), all_language.end()), all_language.end());

	language_cnt = vector<int>(all_language.size());
	for (const auto &language : human)
	{
		language_cnt[query(language)]++;
	}

	int best_voice = -1;
	int best_caption = -1;
	int best_film = -1;

	for (int film_id = 0; film_id < m; film_id++)
	{
		const auto voice_cnt = language_cnt[query(voice[film_id])];
		const auto caption_cnt = language_cnt[query(caption[film_id])];
		if (voice_cnt > best_voice || (voice_cnt == best_voice && caption_cnt >= best_caption))
		{
			best_voice = voice_cnt;
			best_caption = caption_cnt;
			best_film = film_id;
		}
	}

	cout << best_film + 1 << endl;

	return 0;
}