/**
 *    author:  Shivam Gupta
 *    created: 22.10.2021 20:42:57
**/

#include "bits/stdc++.h"
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
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

void solve() {

    int n, k;
    scan(n, k);
    vector<int> a(n);
    scan(a);
    vector<int> x(k), y(k);
    for (int i = 0; i < k; i++) {
        scan(x[i], y[i]);
    }

    int ans = 0;

    vector<pair<int, int>> p;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            p.emplace_back(i, j);
        }
    }

    for (int i = 0; i < 1 << k; i++) {
        vector<int> b = a;
        for (int j = 0; j < k; j++) {
            if (i >> j & 1) {
                swap(b[x[j] - 1], b[y[j] - 1]);
            }
        }
        int v = 0;
        for (int i = 0; i < 1 << p.size(); i++) {
            int s = 0;
            for (int j = 0; j < p.size(); j++) {
                if (i >> j & 1) {
                    s += (b[p[j].second] - b[p[j].first]) * (p[j].second - p[j].first);
                }
            }
            v = max(v, s);
        }
        ans += v;
    }

    print(ans);
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}