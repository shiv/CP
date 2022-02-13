#include "bits/stdc++.h"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second; }
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "["; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "]"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void scan() {} template <typename Head, typename ...Tail> void scan(Head &H, Tail &...T) { cin >> H; scan(T...); }
void print() { cout << "\n"; } template <typename Head> void print(const Head &H) { cout << H << "\n"; } template <typename Head, typename ...Tail> void print(const Head &H, const Tail &...T) { cout << H << " "; print(T...); }
template <typename Head> void dbg_out(string var, const Head &H) { cerr << var << " = " << H << endl; } template <typename Head, typename ...Tail> void dbg_out(string var, const Head &H, const Tail &...T) { for (int i = 0, b = 0; i < (int)var.size(); i++) { if (var[i] == '(' || var[i] == '{') b++; else if (var[i] == ')' || var[i] == '}') b--; else if (var[i] == ',' && b == 0) { cerr << var.substr(0, i) << " = " << H << " | "; dbg_out(var.substr(var.find_first_not_of(' ', i + 1)), T...); break; } } }
#ifndef ONLINE_JUDGE
#define dbg(...) debug = true, dbg_out(#__VA_ARGS__, __VA_ARGS__), debug = false
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

    vector<int> v;

    auto ask = [&] (int a, int b, int c) {
        cout << "? " << a << " " << b << " " << c << endl;
        int r;
        cin >> r;
        if (r == -1) {
            exit(0);
        }
        return r;
    };

    auto say = [&] () {
        sort(v.begin(), v.end());
        // string ans = "!";
        // ans += " " + to_string(v.size());
        // for (int &i : v) {
        //     ans += " " + to_string(i);
        // }
        // cout << ans << endl;
        print("!", v.size(), v); cout.flush();
    };

    int im = -1, cr = -1;
    int last = -1;
    for (int i = 3; i <= n; i++) {
        int curr = ask(i - 2, i - 1, i);
        if (last != -1 && last != curr) {
            if (last == 0 && curr == 1) {
                im = i - 3;
                cr = i;
            }
            else {
                im = i;
                cr = i - 3;
            }
            v.emplace_back(im);
            for (int j = 1; j <= n; j++) {
                if (cr != j && im != j) {
                    if (ask(im, cr, j) == 0) {
                        v.emplace_back(j);
                    }
                }
            }
            say();
            return;
        }
        last = curr;
    }

    if (ask(1, 2, 4) == 0) {
        for (int i = 1; i <= n; i += 3) {
            v.emplace_back(i);
        }
    }
    if (ask(2, 3, 5) == 0) {
        for (int i = 2; i <= n; i += 3) {
            v.emplace_back(i);
        }
    }
    if (ask(3, 4, 6) == 0) {
        for (int i = 3; i <= n; i += 3) {
            v.emplace_back(i);
        }
    }
    say();
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