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

    int n, q;
    scan(n, q);
    string s;
    scan(s);

    auto isP = [&] (const string &s) {

        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (s[i] != s[n - 1 - i]) {
                return false;
            }
        }

        return true;
    };

    vector<vector<int>> p(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        int x = i, y = i;
        while (0 <= x && y < n && s[x] == s[y]) {
            p[x][y] = 1;
            x--, y++;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        int x = i, y = i + 1;
        while (0 <= x && y < n && s[x] == s[y]) {
            p[x][y] = 1;
            x--, y++;
        }
    }
    // for (int i = 0; i < n; i++) {
    //     print(p[i]);
    // }

    auto check = [&] (int x, int y) {

        if ((y - x) & 1) {
            for (int i = x + 1; i + 1 <= y - 1; i += 2) {
                dbg(x, i, i + 1, y);
                if (p[x][i] && p[i + 1][y]) {
                    return true;
                }
            }
        }
        else {
            for (int i = x; i + 1 <= y - 1; i += 2) {
                if (p[x][i] && p[i + 1][y]) {
                    return true;
                }
            }
            for (int i = x + 1; i + 1 <= y; i += 2) {
                if (p[x][i] && p[i + 1][y]) {
                    return true;
                }
            }
        }

        return false;
    };

    while (q--) {

        int l, r;
        scan(l, r);
        l--, r--;

        if (p[l][r] || check(l, r)) {
            print(1);
        }
        else {
            print(0);
        }
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