/**
 *    author:  Shivam Gupta
 *    created: 22.10.2021 15:14:07
**/

#include "bits/stdc++.h"
#include <functional>
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

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

void solve() {

    int n;
    scan(n);
    vector<int> a(n);
    scan(a);

    sort(a.begin(), a.end());

    int ans = inf;

    // for (int i = 0, j = i + 1, k = n - 1; j + 1 < k; j++) {
    //     amin(ans, abs((a[i] - a[j]) - (a[j + 1] - a[k])));
    // }

    int temp = 0;
    for (int i = 0; i < n - 1; i++) {
        temp += abs(a[i] - a[(n - 1) / 2]);
    }
    amin(ans, temp);
    temp = 0;
    for (int i = 1; i < n; i++) {
        temp += abs(a[i] - a[1 + (n - 1) / 2]);
    }
    amin(ans, temp);

    set<int> s(a.begin() + 1, a.end() - 1);
    for (int i = 1; i < n - 1; i++) {
        s.erase(a[i]);
        int diff = abs(a.front() - a[i]);
        auto find = s.lower_bound(a.back() - diff);
        if (find != s.end()) {
            amin(ans, abs(abs(*find - a.back()) - diff));
        }
        if (find != s.begin()) {
            find = prev(find);
            amin(ans, abs(abs(*find - a.back()) - diff));
        }
        s.emplace(a[i]);
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