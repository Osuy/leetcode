#pragma once
#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
using namespace std;
/*
	��վά�޹���ʦ
	��1�Ż�վ����������ÿ����վ1�Σ��ص�n
	dist[i][j] ��dist[j][i]������ͬ

	dfs
		��1������ѭ��ȥÿ����վ��Ȼ�������һ��
*/

void youhui()
{
	auto manjian = [](float& price, int& count)
		{
			auto c = min(price / 100, count);
			count -= c;
			price = price - 10 * c;
		};
	auto dazhe = [](float& price, int& count)
		{
			auto c = max(0, min(1, count));
			count -= c;
			price = price * 0.92;
		};
	auto wumenkan = [](float& price, int& count)
		{
			auto c = min((price + 4) / 5, count);
			count = c;
			price = max(0, price - 5 * c);
		};

	struct solution
	{
		int price, c1, c2, c3; // �Żݺ�ļ۸��ʣ����Ż�ȯ

		bool operator<(const solution& other)const
		{
			// �۸���ͣ���۸���ȵ��Ż�ȯʣ�����
			return price < other.price || ((price == other.price) && (c1 + c2 + c3) > (other.c1 + other.c2 + other.c3));
		}
	};

	array<function<void(solution&)>, 6> youhuis
	{ 
		[&](solution& s) { float p = s.price; dazhe   (p, s.c2); manjian (p, s.c1); s.price = p; },
		[&](solution& s) { float p = s.price; manjian (p, s.c1); dazhe   (p, s.c2); s.price = p; },
		[&](solution& s) { float p = s.price; wumenkan(p, s.c3); manjian (p, s.c1); s.price = p; },
		[&](solution& s) { float p = s.price; manjian (p, s.c1); wumenkan(p, s.c3); s.price = p; },
		[&](solution& s) { float p = s.price; wumenkan(p, s.c3); dazhe   (p, s.c2); s.price = p; },
		[&](solution& s) { float p = s.price; dazhe   (p, s.c2); wumenkan(p, s.c3); s.price = p; },
	};

	int c1, c2, c3;
	std::cin >> c1, c2, c3;

	int n;
	std::cin >> n;

	while (n--)
	{
		int price;
		std::cin >> price;
		solution base{ price, c1, c2, c3 };
		array<solution, 6> s{ base, base, base, base, base, base, };

		youhuis[0](s[0]);
		youhuis[1](s[1]);
		youhuis[2](s[2]);
		youhuis[3](s[3]);
		youhuis[4](s[4]);
		youhuis[5](s[5]);

		cout << (*min_element(s.begin(), s.end())).price << endl;
	}
}


void aichuliqizuhe(const vector<int>& cpu, int n)
{
	vector < vector<int> > ans;
	/*
		����һ�����飬���ڱ�ʾ������0~7�Ƿ����
		0~3λ��һ����·��4~7λ����һ����·
		�ٸ���һ��n��ʾҪ���󼸸�������

		����Ϊ
		1.1324
		2.243
		4��8��һ����������·ȫ��

		����Ϊ������Ƹ����㷨��ֱ��ʹ�ø�������
	*/
	vector<int> l1, l2;

	for (auto el : cpu)
	{
		if (el < 4)l1.push_back(el);
		else l2.push_back(el);
	}

	vector <vector<vector<int>>> strategy(4); // 1248
	if (1 == l1.size())
	{
		strategy[0].push_back(l1);
	}

	if (1 == l2.size())
	{
		strategy[0].push_back(l2);
	}

	if (3 == l1.size())
	{
		strategy[0].push_back(vector<int>(1, l1[0]));
		strategy[0].push_back(vector<int>(1, l1[1]));
		strategy[0].push_back(vector<int>(1, l1[2]));
	}

	if (3 == l2.size())
	{
		strategy[0].push_back(vector<int>(1, l2[0]));
		strategy[0].push_back(vector<int>(1, l2[1]));
		strategy[0].push_back(vector<int>(1, l2[2]));
	}

	if (2 == l1.size())
	{
		strategy[1].push_back(l1);
		strategy[0].push_back(vector<int>(1, l1[0]));
		strategy[0].push_back(vector<int>(1, l1[1]));
	}

	if (2 == l2.size())
	{
		strategy[1].push_back(l2);
		strategy[0].push_back(vector<int>(1, l2[0]));
		strategy[0].push_back(vector<int>(1, l2[1]));
	}

	if (4 == l1.size())
	{
		strategy[0].push_back(vector<int>(1, l1[0]));
		strategy[0].push_back(vector<int>(1, l1[1]));
		strategy[0].push_back(vector<int>(1, l1[2]));
		strategy[0].push_back(vector<int>(1, l1[3]));


		strategy[1].push_back(vector<int>{ l1[0], l1[1] });
		strategy[1].push_back(vector<int>{ l1[0], l1[2] });
		strategy[1].push_back(vector<int>{ l1[0], l1[3] });
		strategy[1].push_back(vector<int>{ l1[1], l1[2] });
		strategy[1].push_back(vector<int>{ l1[1], l1[3] });
		strategy[1].push_back(vector<int>{ l1[2], l1[3] });


		strategy[3].push_back(l1);
	}

	if (4 == l2.size())
	{
		strategy[0].push_back(vector<int>(1, l2[0]));
		strategy[0].push_back(vector<int>(1, l2[1]));
		strategy[0].push_back(vector<int>(1, l2[2]));
		strategy[0].push_back(vector<int>(1, l2[3]));

		strategy[1].push_back(vector<int>{ l2[0], l2[1] });
		strategy[1].push_back(vector<int>{ l2[0], l2[2] });
		strategy[1].push_back(vector<int>{ l2[0], l2[3] });
		strategy[1].push_back(vector<int>{ l2[1], l2[2] });
		strategy[1].push_back(vector<int>{ l2[1], l2[3] });
		strategy[1].push_back(vector<int>{ l2[2], l2[3] });


		strategy[2].push_back(l2);
	}

	if (3 == l1.size())
	{
		strategy[1].push_back(vector<int>{ l1[0], l1[1] });
		strategy[1].push_back(vector<int>{ l1[0], l1[2] });
		strategy[1].push_back(vector<int>{ l1[1], l1[2] });
	}

	if (3 == l2.size())
	{
		strategy[1].push_back(vector<int>{ l2[0], l2[1] });
		strategy[1].push_back(vector<int>{ l2[0], l2[2] });
		strategy[1].push_back(vector<int>{ l2[1], l2[2] });
	}

	if (l1.size() + l2.size() == 8)
	{
		vector<int>tmp;
		tmp.reserve(8);
		std::iota(tmp.begin(), tmp.end(), 0);// 0~7
		strategy[3].push_back(std::move(tmp));
	}


	int n;
	cin >> n;
	ans = strategy[n];
}

struct pos
{
	int x = 0, y = 0;
	int x2 = 0, y2 = 0;
};
void aishibieban(vector<pos>& lights)
{
	/*
		�Ե�����ʣ��δ����ĵ��У�ȡ��ߵģ�yֵ��С����������ߵĵƲ�����뾶�ĵ��������
		Ȼ���ظ�
	*/
	int base = lights[0].y;
	float radius = lights[0].y2 - base;
	radius /= 2;
	std::sort(lights.begin(), lights.end(), [](const pos& l, const pos& r) {return l.y < r.y; });

	// �ҵ���һ������ߵƲ���ͬһ�еĵ�
	auto start = lights.begin();
	auto end = std::find_if(lights.begin(), lights.end(), [base, radius](const pos& l) { return l.y > base + radius; });

	while (lights.end() != end)
	{
		// �����䰴xֵ����
		std::sort(start, end, [](const pos& l, const pos& r) { return l.x < r.x; });
		start = end;
		base = start->y;
		end = std::find_if(start, lights.end(), [base, radius](const pos& l) { return l.y > base + radius; });
	}	

	std::sort(start, end, [](const pos& l, const pos& r) { return l.x < r.x; });
}

void mvpzhengduozhan(vector<int>& scores)
{
	/*
		��scores���֣����������������ܴ�ʱ��ÿ��ĺ�
	*/

	sort(scores.begin(), scores.end());

	auto sum = accumulate(scores.begin(), scores.end(), 0);
	auto average = sum;
	auto ans = -1;
	vector<bool> used(scores.size(), false);
	unordered_map<vector<bool>, bool>visited;
	auto dfs = [&](this auto&& dfs, int team, int count, int start)->bool
		{
			if (team == 0)
			{
				return true;
			}

			if (visited.contains(used))
			{
				return visited[used];
			}

			if (count == 0)
			{
				visited[used] = dfs(team - 1, average, 0);
				return visited[used];
			}

			for (int j = start; j < scores.size(); ++j)
			{
				if (scores[j] > count)break;
				if (used[j])continue;
				if (j > 0 && !used[j - 1] && scores[j - 1] == scores[j])continue;

				used[j] = true;
				if (dfs(team, count - scores[j], j+1))return true;
				used[j] = false;
			}

			return false;
		};

	auto t = scores.size();
	while (t--)
	{
		if (sum % t)continue;
		average = sum / t;

		
		visited.clear();
		if (dfs(t, average, 0))break;
	}
}

void vlanziyuanchi()
{
	string str;
	stringstream ss;
	int n;
	cin >> n;
	while (getline(cin, str, ','))
	{
		auto pos = str.find('-');
		if (string::npos == pos) 
		{
			if (atoi(str.c_str()) == n)
			{
				continue;
			}
		}
		else
		{
			auto start = atoi(str.substr(0, pos).c_str());
			auto end = atoi(str.substr(pos + 1).c_str());
			if (n == end)
			{
				str = to_string(start) + '-' + to_string(end - 1);
			}
			else if (n == start)
			{
				str = to_string(start + 1) + '-' + to_string(end);
			}
			else if (n < end && n > start)
			{
				ss << (to_string(start) + '-' + to_string(n - 1));
				str = to_string(n + 1) + '-' + to_string(end);
			}
		}

		ss << str;
	}
}

int fenpingguo(vector<int>& apple)
{
	/*
		��ƻ�������ͷ�ʽ����Ϊ���ݣ���ʹ����һ�ݾ����ܵش�

		���类��Ϊ����������ȵ�a��b����a^b = 0
		��������Ҫ�������������Ƿ�Ϊ0

		���������Ϊ0������СԪ������������Ԫ�ص��������
	*/

	auto xorsum = 0;
	auto sum = 0;
	auto minval = 0;
	for (auto el : apple)
	{
		xorsum ^= el;
		sum += el;
		minval = min(minval, el);
	}

	if (xorsum)return -1;

	return sum - minval;
}

int huobihuansuan(const vector<string>& money)
{
	auto sum = 0;

	for (auto& el : money)
	{
		auto pos = el.find_first_of("CJHEG");
		// �������Ԫ
		if (string::npos != pos)
		{
			auto yuan = atoi(el.substr(0, pos).c_str());
			switch (el[pos])
			{
			case 'C': sum += 100 * yuan; break;
			case 'J': sum += (float)yuan / 1825 * 10000; break;
			case 'H': sum += (float)yuan / 123 * 10000; break;
			case 'E': sum += (float)yuan / 14 * 10000; break;
			case 'G': sum += (float)yuan / 12 * 10000; break;
			default:
				break;
			}

			pos += 3;
		}
		else
		{
			pos = 0;
		}

		// ���������
		auto pos2 = el.find_first_of("fcsep");
		if (string::npos != pos2)
		{
			auto fen = atoi(el.substr(pos, pos2).c_str());
			switch (el[pos2])
			{
			case 'f': sum += fen; break;
			case 'c': sum += (float)fen / 1825 * 100; break;
			case 's': sum += (float)fen / 123 * 100; break;
			case 'e': sum += (float)fen / 14 * 100; break;
			case 'p': sum += (float)fen / 12 * 100; break;
			default:
				break;
			}
		}

	}
}

int wanmeizouwei(string& str)
{
	/*
		str���ɴ�д��ĸWASD���
		�޸����е�һ���ִ���ʹ�ĸ���ĸ��
	*/
	auto len = str.length();

	int counts[4] = { 0, 0, 0, 0, };
	for (auto& el : str)
	{
		switch (el)
		{
		case 'W':counts[0]++; el = 'a'; break;
		case 'A':counts[1]++; el = 'b'; break;
		case 'S':counts[2]++; el = 'c'; break;
		case 'D':counts[3]++; el = 'd'; break;
		default:
			break;
		}
	}


	if (counts[0] == counts[2] || counts[1] == counts[3])
	{
		return 0;
	}
	auto average = len / 4;

	// wasdaasd
	// 1 2 2 2
	// wwwwaaaassss
	// 4 3 4 0
	int ans = len;
	auto l = 0, r = 0; // ��������������
	while (r < len)
	{
		// ��չ�ҽ磬��������
		counts[str[r] - 'a']--;
		r++;

		// ��������ĸ���ĸ�������ڵ���ƽ��ʱ��˵���޸�������ϣ���ʼ��С���䣬����¼��С�Ĵ�
		while (counts[0] <= average && counts[1] <= average && counts[2] <= average && counts[3] <= average)
		{
			ans = min(ans, r - l);
			counts[str[l] - 'a']++;
			l++;

		}
	}

	return ans;
}


int jizhan(const vector<vector<int>>& matrix)
{
	int min_dist = INT_MAX;
	auto N = matrix.size();
	vector<bool> used;
	used[0] = true; // �����Ϊ�Ѿ���
	auto dfs = [&](this auto&& dfs, int n, int last_node, int dist)
		{
			if (n >= N) // �Ѿ��߹������е㣬��ص���㣬�������·��
			{
				min_dist = min(min_dist, dist + matrix[last_node][0]);
				return;
			}

			for (int i = 1; i < N; ++i)
			{
				if (used[i])continue;
				used[i] = true;
				dfs(n + 1, i, dist + matrix[last_node][i]);
				used[i] = false;
			}
		};

	dfs(1, 0, 0);
	return min_dist;

}

string minganci(const string& str, int k)
{
	/*
		�������ַ����ڵĵ�k�������滻Ϊ******
		�����ַ���������ĸ�����»��ߺ�ż��������
		��������֮����һ�������»��߸�����������������»���������ĳɷ�

		password__a12345678_timeout_100
	*/
	stringstream ss{};

	// ���������»���
	auto dfs2 = [&](this auto&& dfs2, string_view str)
		{
			if (str.empty())return;
			auto start = str.find_first_not_of('_');
			if (string::npos == start)
			{
				if (!ss.view().empty())
				{
					ss << '_';
				}
				ss << str;
			}
			else
			{
				auto end = str.find_first_of('_', start);
				if (!ss.view().empty())
				{
					ss << '_';
				}

				if (k == 0)
				{
					ss << "******";
				}
				else
				{
					ss << str.substr(start, end - start);
				}
				k--;

				while (end < str.length() && str[end] == '_')++end;

				if (end < str.length())
				{
					dfs2(str.substr(end));
				}
			}
		};

	// ���������ַ����е�����
	auto dfs = [&](this auto&& dfs, string_view str)->void
		{
			auto start = str.find_first_of('\"');
			dfs2(str.substr(0, start)); // ����ǰ���֣��Ǻ��»����ַ���

			if (string::npos != start)
			{
				if (0 != ss.tellp())
				{
					ss << '_';
				}

				auto end = str.find_first_of('\"', start + 1);// ��start+1��ʼѰ����һ������
				ss << '\"' << str.substr(start + 1, end - start - 1) // �����ڲ��������������ֱ������
				   << '\"';

				dfs(str.substr(end + 1));// ���ź󲿷֣����ܻ������ţ��ݹ�
			}
		};

	dfs(str);
}

void shuzuerchashu(vector<int>& nums)
{
	/*
		0
		1 2
		3 4 5 6
	*/
	int min_index = -1;
	auto dfs = [&](this auto&& dfs, int i)->bool
		{
			if (i >= nums.size())return false;

			if (-1 == nums[i])return false;

			auto has_l = dfs(i * 2 + 1);
			auto has_r = dfs(i * 2 + 2);
			if (!has_l && !has_r)
			{
				if (-1 == min_index)
				{
					min_index = i;
				}
				else if(nums[min_index] > nums[i])
				{
					min_index = i;
				}
			}

			return true;
		};

	dfs(0);

	vector<int> st;
	while (min_index > 0)
	{
		st.push_back(nums[min_index]);
		min_index = (min_index - 1) / 2;
	};

	cout << nums[0];
	while (!st.empty())
	{
		cout << st.back();
		st.pop_back();
	}
}

int tanxinshangren(vector<int>& counts, vector<vector<int>>& prices)
{
	int earn = 0;
	for (int i = 0; i < counts.size(); ++i)
	{
		const auto& pr = prices[i];

		int profit = 0;
		for (int j = 1; j < pr.size(); ++j)
		{
			if (pr[j] > pr[j - 1])
			{
				profit += (pr[j] - pr[j - 1]);
			}
		}

		earn += counts[i] * profit;
	}
}

void youxiuyuangong()
{
	struct stuff_info
	{
		int id = -1;
		int count = 0;
		int first_card = INT_MAX;

		bool operator<(const stuff_info& info)const
		{
			return count > info.count ||
				(count == info.count && (first_card < info.first_card || (first_card == info.first_card && id < info.id)));
		}
	};
	int N = 0;
	cin >> N;
	vector<stuff_info> vec(N);
	vector<int> day_count(30, 0);
	for (int i = 0; i < 30; ++i)
	{
		cin >> day_count[i];
	}

	for (int i = 0; i < 30; ++i)
	{
		int id = 0;
		auto count = day_count[i];
		while (count--)
		{
			cin >> id;
			if (vec[id].id == -1)
			{
				vec[id].id = id;
				vec[id].first_card = i;
			}
			vec[id].count++;
		}
	}

	priority_queue<stuff_info> q(vec.begin(), vec.end());
}