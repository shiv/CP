#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second;}
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "{"; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "}"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void scan() {} template <typename Head, typename ...Tail> void scan(Head &H, Tail &...T) { cin >> H; scan(T...); }
void print() { cout << "\n"; } template <typename Head> void print(const Head &H) { cout << H << "\n"; } template <typename Head, typename ...Tail> void print(const Head &H, const Tail &...T) { cout << H << " "; print(T...); }
void dbg_out() { cerr << "\n"; } template <typename Head, typename ...Tail> void dbg_out(const Head &H, const Tail &...T) { cerr << " " << H; dbg_out(T...); }
#ifndef ONLINE_JUDGE
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug = true, dbg_out(__VA_ARGS__), debug = false
#else
#define dbg(...)
#endif

#define int int64_t

struct datas {
    string name;
    int department;
    datas(string n, int d) {
        name = n;
        department = d;
    }
};

signed main() {

    int n, m;
    cin >> n >> m;
    int A, B;
    cin >> A >> B;
    vector<int> t(3);
    cin >> t[0] >> t[1] >> t[2];

    vector<datas> data;
    map<string, int> d, hash;
    string name;
    int dep;
    for (int i = 0; i < n; i++) {
        cin >> name >> dep;
        d[name] = dep - 1;
    }
    for (auto &l : d) {
        hash[l.first] = data.size();
        data.push_back(datas(l.first, l.second));
    }

    const int M = n;
    vector<int> parent(M);
    vector<vector<int>> tot(M, vector<int>(3));
    for (int i = 0; i < M; i++) {
        parent[i] = i;
        tot[i][data[i].department] = 1;
    }

    function<int (int)> find_set = [&] (int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = find_set(parent[v]);
    };

    auto union_sets = [&] (int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            int res = 0;
            for (int i = 0; i < 3; i++) {
                if (tot[a][i] + tot[b][i] > t[i]) {
                    return;
                }
                res += tot[a][i] + tot[b][i];
            }
            if (res > B) {
                return;
            }
            for (int i = 0; i < 3; i++) {
                int temp = tot[a][i];
                tot[a][i] = 0;
                tot[b][i] += temp;
            }
            parent[a] = b;
        }
    };

    for (int i = 0; i < m; i++) {
        string a, b;
        cin >> a >> b;
        union_sets(hash[a], hash[b]);
    }

    vector<vector<int>> nums(n);
    for (int i = 0; i < n; i++) {
        nums[find_set(i)].push_back(i);
    }

    int mm = 0;
    for (auto &kk : nums) {
        mm = max<int>(mm, kk.size());
    }

    if (mm < A) {
        cout << "no groups";
        return 0;
    }

    vector<string> res;

    for (auto &k : nums) {
        if (k.size() == mm) {
            for (auto &l : k) {
                res.emplace_back(data[l].name);
            }
        }
    }

    sort(res.begin(), res.end());
    for (auto &k : res) {
        cout << k << '\n';
    }

    return 0;
}
