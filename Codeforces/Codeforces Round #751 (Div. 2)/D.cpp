/**
 *    author:  Shivam Gupta
 *    created: 03.11.2021 13:19:18
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

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

void solve() {

    int n;
    scan(n);
    vector<int> a(n), b(n);
    scan(a);
    scan(b);

    a.insert(a.begin(), 0);
    b.insert(b.begin(), 0);

    vector<int> c(n + 1);
    for (int i = 0; i <= n; i++) {
        c[i] = i + b[i];
    }

    vector<vector<int>> v(n + 1);
    for (int i = 0; i <= n; i++) {
        if (c[i] < n) {
            v[c[i]].push_back(i);
        }
    }
    dbg(v);

    vector<int> d(n + 1);
    iota(d.begin(), d.end(), 0);
    sort(d.begin(), d.end(), [&] (int i, int j) {
        return i - a[i] < j - a[j];
    });
    dbg(d);

    int idx = 0, idy = 0;
    vector<int> dp(n, inf);
    dp[0] = 0;
    for (int i = 0; i <= n; i++) {
        while (idx < n && i - d[idx] > 0) {
            idx += 1;
        }
        // while (idy < n && d[idy] - i)
        for (int& j : v[i]) {

        }
        dbg(idx);
    }
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}