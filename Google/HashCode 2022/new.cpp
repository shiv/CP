#include "bits/stdc++.h"
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second; }
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "["; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "]"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void scan() {} template <typename Head, typename ...Tail> void scan(Head &H, Tail &...T) { cin >> H; scan(T...); }
void print() { cout << "\n"; } template <typename Head> void print(const Head &H) { cout << H << "\n"; } template <typename Head, typename ...Tail> void print(const Head &H, const Tail &...T) { cout << H << " "; print(T...); }
template <typename Head> void dbg_out(string var, const Head &H) { cerr << var << " = " << H << endl; } template <typename Head, typename ...Tail> void dbg_out(string var, const Head &H, const Tail &...T) { for (int i = 0, b = 0; i < (int)var.size(); i++) { if (var[i] == '(' || var[i] == '{') b++; else if (var[i] == ')' || var[i] == '}') b--; else if (var[i] == ',' && b == 0) { cerr << var.substr(0, i) << " = " << H << " | "; dbg_out(var.substr(var.find_first_not_of(' ', i + 1)), T...); break; } } }
#ifndef ONLINE_JUDGE
#define dbg(...) debug = true, dbg_out(#__VA_ARGS__, __VA_ARGS__), debug = false
#else
#define dbg(...)
#endif

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

struct pskill {
	int no;
	int level;
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }

void solve() {

  int c, p;
  scan(c, p);

	// skill
  unordered_map<string, int> shash;
  vector<string> srhash;

	// skill[level, person_id]
	vector<multiset<pair<int, int>>> con_avail;

	// contributor
  vector<string> cname(c);
  unordered_map<string, int> chash;
  vector<vector<pair<int, int>>> cskills(c);

  for (int i = 0; i < c; i++) {
    int nos;
    scan(cname[i], nos);
    chash[cname[i]] = i;
    for (int j = 0; j < nos; j++) {
      string skill;
			int level;
      scan(skill, level);
      if (shash.find(skill) == shash.end()) {
        shash[skill] = shash.size();
				srhash.emplace_back(skill);
				con_avail.emplace_back(multiset<pair<int, int>>());
      }
      cskills[i].emplace_back(shash[skill], level);
			con_avail[shash[skill]].emplace(level, i);
    }
  }

	// project
	vector<string> pname(p);
	vector<int> d(p), s(p), b(p), r(p);
	vector<int> start(p);
	vector<vector<pair<int, int>>> pskills(p);

	for (int i = 0; i < p; i++) {
		scan(pname[i], d[i], s[i], b[i], r[i]);
		start[i] = b[i] - d[i];
    // dbg(pname[i], r[i]);
		for (int j = 0; j < r[i]; j++) {
			string skill;
			int level;
			scan(skill, level);
      pskills[i].emplace_back(shash[skill], level);
		}
	}

  vector<int> order(p);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&] (auto &x, auto &y) {
		return start[x] < start[y];
  });

    // shuffle(order.begin(), order.end(), rng);

	vector<vector<int>> hired(p);
	
	// due[i] is vector of projects whose due date is `due`
	vector<vector<int>> due(1e5 + 1);
    int score = 0;

	vector<int> vs;

	int it = 0;
  for (int time = 1; time <= 100000; time++) {
      
	  while (it < order.size() && start[order[it]] < time) 
	  	it++;
		if (it == order.size())
			break;
		while (it < order.size() && start[order[it]] == time) {
			int i = order[it];
		
    // dbg(pname[i]);
		// i is the project number
		int sz = pskills[i].size();
		vector<bool> used(sz);
		vector<int> hire(sz);
		map<int, int> maxLvl;
		bool ok = true;
		for (int j = 0; j < sz; j++) {
			auto &[skill_id, level] = pskills[i][j];
			auto lb = con_avail[skill_id].lower_bound({level, -1});
			if (lb != con_avail[skill_id].end()) {
				int person_hired = lb -> second;
				hire[j] = person_hired;
				hired[i].emplace_back(person_hired);
				// for (int &banda : hired[i]) {
				for (auto &[hunar, myLevel] : cskills[person_hired]) {
					con_avail[hunar].erase({myLevel, person_hired});
					amax(maxLvl[hunar], myLevel);
				}
				// }
				used[j] = true;
			}
		}

		for (int j = 0; j < sz; j++) {
			if (used[j])
				continue;
			auto &[skill_id, level] = pskills[i][j];
			int dec = maxLvl[skill_id] >= level;
			auto lb = con_avail[skill_id].lower_bound({level - dec, -1});
			if (lb != con_avail[skill_id].end()) {
				int person_hired = lb -> second;
				hire[j] = person_hired;
				hired[i].emplace_back(person_hired);
				// for (int &banda : hired[i]) {
				for (auto &[hunar, myLevel] : cskills[person_hired]) {
					con_avail[hunar].erase({myLevel, person_hired});
					amax(maxLvl[hunar], myLevel);
				}
				// }
				used[j] = true;
			}
			else {
				ok = false;
				break;
				for (int &banda : hired[i]) {
					for (auto &[hunar, myLevel] : cskills[banda]) {
						con_avail[hunar].emplace(myLevel, banda);
					}
				}
				hired[i].clear();
				break;
			}
		}

		if (!ok) {
			for (int &banda : hired[i]) {
				for (auto &[hunar, myLevel] : cskills[banda]) {
					con_avail[hunar].emplace(myLevel, banda);
				}
			}
			hired[i].clear();
		}
		else {
			hired[i].clear();
			for (int j = 0; j < sz; j++) {
				hired[i].emplace_back(hire[j]);
			}
		}
		

		if (!hired[i].empty()) {
			vs.emplace_back(i);
			due[b[i]].emplace_back(i);
			score += s[i];
		}

		it++;
		}


		for (auto &project : due[time]) {
        int sz = pskills[project].size();
        if (hired[project].empty())
          continue;
        assert(hired[project].size() == sz);
        for (int j = 0; j < sz; j++) {
          auto [hunarInUse, levelRequired] = pskills[project][j];
          int banda = hired[project][j];
					for (auto &[hunar, myLevel] : cskills[banda]) {
							if (hunar == hunarInUse && myLevel == levelRequired) {
									myLevel++;
									// dbg(srhash[hunar], cname[banda]);
							}
							con_avail[hunar].emplace(myLevel, banda);
					}
        }
      }
      due[time].clear();
		

  }

  dbg(score);

	print(vs.size());

	for (auto &project : vs) {
		print(pname[project]);
		vector<string> people;
		for (auto &person_hired : hired[project]) {
			people.emplace_back(cname[person_hired]);
		}
		print(people);
	}

}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;

    for (int tt = 1; tt <= t; tt++) {
			solve();
    }

    return 0;
}