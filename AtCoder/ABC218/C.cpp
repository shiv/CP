#include "bits/stdc++.h"
#include <algorithm>
#include <iostream>
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

    int n;
    scan(n);
    vector<string> s(n);
    scan(s);
    vector<string> t(n);
    scan(t);


    auto doit = [&] (vector<string> st) {
        vector<bool> row(n, false), column(n, false);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (st[i][j] == '#') {
                    row[i] = true;
                }
            }
        }
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                if (st[i][j] == '#') {
                    column[j] = true;
                }
            }
        }

        int r1, r2, c1, c2;
        for (r1 = 0; r1 < n; r1++) {
            if (row[r1]) {
                break;
            }
        }
        for (r2 = n - 1; r2 >= 0; r2--) {
            if (row[r2]) {
                break;
            }
        }
        for (c1 = 0; c1 < n; c1++) {
            if (column[c1]) {
                break;
            }
        }
        for (c2 = n - 1; c2 >= 0; c2--) {
            if (column[c2]) {
                break;
            }
        }

        vector<string> res;
        for (int i = r1; i <= r2; i++) {
            string temp;
            for (int j = c1; j <= c2; j++) {
                temp += st[i][j];
            }
            res.emplace_back(temp);
        }

        return res;
    };

    auto rotate = [&] (const vector<string> &st) {
        vector<string> res = st;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = st[j][n - 1 - i];
            }
        }
        return res;
    };

    auto s1 = doit(s);
    s = rotate(s);
    auto s2 = doit(s);
    s = rotate(s);
    auto s3 = doit(s);
    s = rotate(s);
    auto s4 = doit(s);
    auto t_ = doit(t);

    if (t_ == s1 || t_ == s2 || t_ == s3 || t_ == s4) {
        print("Yes");
    }
    else {
        print("No");
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