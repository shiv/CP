/**
 *    author:  Shivam Gupta
 *    created: 09.08.2021 11:27:37
**/

#include "bits/stdc++.h"
#include <iomanip>
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
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 3e5 + 5;

void preSolve(int &t) {
    cin >> t;
}

#define ld long double
ld eps = 1e-12;

void solve(int tc = 0) {
    ld limit = 1e-10;
    cout << fixed << setprecision(11);
    ld c, m, p, v;
    cin >> c >> m >> p >> v;

    ld ans = 0;
    function<void (ld, ld, ld, ld, int)> doit = [&] (ld C, ld  M, ld P, ld curr, int cnt) {
        ld res = P * cnt * curr;
        if (res < eps) {
            return;
        }
        ans += res;

        if (C > eps && M > eps) {
            ld cc = min<ld>(C, v);
            ld mm = min<ld>(M, v);
            doit(C - cc, M + cc / 2, P + cc / 2, curr * C, cnt + 1);
            doit(C + mm / 2, M - mm, P + mm / 2, curr * M, cnt + 1);
        }
        else if (C > eps) {
            ld cc = min<ld>(C, v);
            doit(C - cc, M, P + cc, curr * C, cnt + 1);
        }
        else if (M > eps) {
            ld mm = min<ld>(M, v);
            doit(C, M - mm, P + mm, curr * M, cnt + 1);
        }
    };

    doit(c, m, p, 1, 1);
    print(ans);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}
