#include "bits/stdc++.h"
#include <utility>
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

class dsu {
public:
    vector<int> p, r;
    int n;

    dsu(int _n) : n(_n) {
        p.assign(n, 0);
        r.assign(n, 0);
        iota(p.begin(), p.end(), 0);
    }

    inline int get(int x) {
        return x == p[x] ? x : (p[x] = get(p[x]));
    }

    inline bool unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (x != y) {
            if (r[x] < r[y]) swap(x, y);
            p[y] = x;
            if (r[x] == r[y]) r[x]++;
            return true;
        }
        return false;
    }
};

int solve(int n, vector<vector<int>> edges, vector<int> a) {

    vector<vector<int>> g(n);
    for (auto &e : edges) {
        int u = e[0] - 1, v = e[1] - 1;
        a[u] > a[v] ? g[u].push_back(v) : g[v].push_back(u);
    }

    map<int, vector<int>> m;
    for (int i = 0; i < n; i++) {
        m[a[i]].push_back(i);
    }

    int ans = 0;
    dsu d(n);

    for (auto &[num, indices] : m) {
        for (int &u : indices) {
            for (int &v : g[u]) {
                d.unite(u, v);
            }
        }
        map<int, int> temp;
        for (auto &u : indices) {
            temp[d.get(u)] += 1;
        }
        for (auto &[i, j] : temp) {
            ans += j * (j - 1) / 2;
        }
    }

    return ans;
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        cout << solve(6, {{1, 2}, {1, 3}, {3, 4}, {3, 5}, {2, 6}}, {2, 3, 1, 2, 3, 3}) << endl;
        cout << solve(5, {{2, 1}, {3, 1}, {4, 1}, {5, 1}}, {1, 3, 1, 2, 3}) << endl;
    }

    return 0;
}