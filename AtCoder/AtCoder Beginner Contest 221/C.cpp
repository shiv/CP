/**
 *    author:  Shivam Gupta
 *    created: 06.11.2021 10:55:43
**/

#include "bits/stdc++.h"
#include <algorithm>
#include <string>
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

    // vector<int> v;

    // while (n) {
    //     v.push_back(n % 10);
    //     n /= 10;
    // }

    // sort(v.begin(), v.end(), greater<int>());
    // int a = 0, b = 0;

    // for (int i = 1; i < v.size(); i += 2) {
    //     a = a * 10 + v[i - 1];
    //     b = b * 10 + v[i];
    // }

    // if (v.size() % 2 == 1) {
    //     b = b * 10 + v.back();
    // }

    string s = to_string(n);
    int sz = s.size();
    sort(s.begin(), s.end());

    int ans = 0;

    do {
        for (int i = 1; i < sz; i++) {
            string c = s.substr(0, i);
            string d = s.substr(i, sz - i);
            if (c[0] != '0' && d[0] != '0') {
                int a = stoi(c);
                int b = stoi(d);
                ans = max(ans, a * b);
            }
        }
    } while (next_permutation(s.begin(), s.end()));

    print(ans);
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