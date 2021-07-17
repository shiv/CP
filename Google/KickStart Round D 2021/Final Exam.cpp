/**
 *    author:  Shivam Gupta
 *    created: 11.07.2021 11:09:45
**/

#include "bits/stdc++.h"
#include <algorithm>
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second;}
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "{"; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "}"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void out(bool ok, bool cap = true) { cap ? cout << (ok ? "YES" : "NO") : cout << (ok ? "Yes" : "No"); cout << "\n"; }
void print() { cout << "\n"; } template <typename Head> void print(Head H) { cout << H << "\n"; } template <typename Head, typename... Tail> void print(Head H, Tail... T) { cout << H << " "; print(T...); }
void dbg_out() { cerr << "\n"; } template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << " " << H; dbg_out(T...); }
#ifndef ONLINE_JUDGE
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug = true, dbg_out(__VA_ARGS__), debug = false
#else
#define dbg(...)
#endif

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 1e3 + 1;

void preSolve(int &t) {
    cin >> t;
}

void solve(int tc = 0) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i] >> b[i];
    vector<int> s(m);
    cin >> s;

    vector<int> ans;
    set<pair<int, int>> ss;

    auto in = [&] (int a, int b) {
        if (a <= b)
            ss.insert({a, b});
    };

    for (int i = 0; i < n; i++)
        in(a[i], b[i]);

    for (int &curr : s) {
        auto p = ss.upper_bound({curr, curr});

        if (p == ss.begin()) {
            ans.push_back(p->first);
            in(p->first + 1, p->second);
            ss.erase(p);
            continue;
        }

        p = prev(p);

        if (p->first <= curr && curr < p->second) {
            ans.push_back(curr);
            in(p->first, curr - 1);
            in(curr + 1, p->second);
            ss.erase(p);
            continue;
        }

        auto n = p;
        if (n != ss.end() && next(n) != ss.end())
            n = next(n);

        if (abs(p->second - curr) <= abs(n->first - curr)) {
            ans.push_back(p->second);
            in(p->first, p->second - 1);
            ss.erase(p);
        }
        else {
            ans.push_back(n->first);
            in(n->first + 1, n->second);
            ss.erase(n);
        }
    }

    print(ans);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve(i);
    }
    return 0;
}