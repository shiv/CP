#include "bits/stdc++.h"
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

    string s = to_string(n);
    int digits = s.size();

    vector<int> dp(16);
    for (int i = 1; i < 16; i++) {
        dp[i] = dp[i - 1];
        int nine = 1;
        for (int j = 1; j <= i; j++) {
            dp[i] += nine * (i - j + 1);
            nine *= 9 + (nine != 1);
        }
    }

    // vector<int> ten(16, 1);
    // for (int i = 1; i < 16; i++) {
    //     ten[i] = ten[i - 1] * 10;
    // }

    // for (int i = 0; i < digits; i++) {
    //     if (s[i] >= '1') {
    //         ans += dp[to_string(n).size() - 1];
    //     }
    //     if (s[i] == '1') {
    //         break;
    //     }
    //     n = stoll(to_string(n).substr(1));
    //     dbg(n);
    //     // ans += n % ten[digits - i - 1];
    //     ans += n;
    // }
    int ans = 0;

    if (set<int>(s.begin(), s.end()).size() == 1 && s[0] == '1') {
        ans += 1;
    }

    while (!s.empty()) {
        if (s[0] == '0') {
            // ans += digits - s.size() - 1;
            break;
        }
        if (s[0] == '1') {
            ans += dp[s.size() - 1];
        }
        if (s[0] > '1') {
            ans += dp[s.size()];
            break;
        }
        s = s.substr(1);
        if (!s.empty()) {
            ans += stoll(s);
        }
    }

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