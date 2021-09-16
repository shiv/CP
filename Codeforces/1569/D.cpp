#include "bits/stdc++.h"
#include <algorithm>
#include <functional>
#include <vector>
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
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 1e6 + 5;

void solve() {

    int n, m, k;
    scan(n, m, k);
    vector<int> x(n), y(m);
    scan(x, y);
    vector<pair<int, int>> p(k);
    scan(p);

    vector<vector<int>> xx(N), yy(N);
    vector<int> X, Y;

    for (auto &[a, b] : p) {
        xx[a].emplace_back(b);
        yy[b].emplace_back(a);
        X.push_back(b);
        Y.push_back(a);
    }

    for (auto &v : xx) {
        sort(v.begin(), v.end());
    }
    for (auto &v : yy) {
        sort(v.begin(), v.end());
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());

    int ans = 0;
    for (auto [x_, y_] : p) {
        dbg(x_, y_, ans);
        bool isx = binary_search(x.begin(), x.end(), x_);
        bool isy = binary_search(y.begin(), y.end(), y_);
        if (isx && isy) {
            continue;
        }
        if (isx) {
            int nxt = upper_bound(y.begin(), y.end(), y_) - y.begin();
            int prv = nxt - 1;
            ans += lower_bound(X.begin(), X.end(), y[nxt]) - X.begin();
            ans -= upper_bound(X.begin(), X.end(), y[prv]) - X.begin();
            int idx = lower_bound(x.begin(), x.end(), x_) - x.begin();
            auto &v = xx[x[idx]];
            ans -= lower_bound(v.begin(), v.end(), y[prv]) - v.begin();
            ans += upper_bound(v.begin(), v.end(), y[nxt]) - v.begin();
        }
        if (isy) {
            int nxt = upper_bound(x.begin(), x.end(), x_) - x.begin();
            int prv = nxt - 1;
            ans += lower_bound(Y.begin(), Y.end(), x[nxt]) - Y.begin();
            ans -= upper_bound(Y.begin(), Y.end(), x[prv]) - Y.begin();
            int idy = lower_bound(y.begin(), y.end(), y_) - y.begin();
            auto &v = yy[y[idy]];
            ans -= lower_bound(v.begin(), v.end(), x[nxt]) - v.begin();
            ans += upper_bound(v.begin(), v.end(), x[prv]) - v.begin();
        }
    }

    print(ans / 2);
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