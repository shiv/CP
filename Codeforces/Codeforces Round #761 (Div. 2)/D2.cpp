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

template <typename A, typename B> string to_string(pair<A, B> p);
string to_string(const char& ch) { return string(1, ch); }
string to_string(const string& s) { return s; }
string to_string(const char* s) { return to_string((string) s); }
template <typename A> string to_string(A v) { bool first = true; string res = ""; for (const auto &x : v) { if (!first) { res += " "; } first = false; res += to_string(x); } res += " "; return res; }
template <typename A, typename B> string to_string(pair<A, B> p) { return to_string(p.first) + " " + to_string(p.second); }
template <typename Head> string attach(const Head &H) { return to_string(H); }
template <typename Head, typename ...Tail> string attach(const Head &H, const Tail &...T) { return to_string(H) + " " + attach(T...); }

void solve() {

    int n;
    scan(n);

    vector<int> v;

    map<set<int>, int> mp;

    auto ask = [&] (int a, int b, int c) {
        cout << attach("?", a, b, c) << endl;
        // cout << "? " << a << " " << b << " " << c << endl;
        int r;
        cin >> r;
        if (r == -1) {
            exit(0);
        }
        return r;
    };

    auto say = [&] () {
        sort(v.begin(), v.end());
        // cout << attach("!", v.size(), v) << endl;
        print("!", v.size(), v); cout.flush();
        // ans += "! " + to_string(v.size());
        // for (int &i : v) {
        //     ans += " " + to_string(i);
        // }
        // cout << ans << endl;
    };

    int im = -1, cr = -1;
    int last = -1;
    vector<int> vis(n + 1);
    vector<int> imposter(n + 1, 0);
    for (int i = 3; i <= n; i++) {
        int curr = ask(i - 2, i - 1, i);
        vis[i] = curr;
        if (last != -1 && last != curr) {
            if (last == 0 && curr == 1) {
                im = i - 3;
                cr = i;
            }
            if (last == 1 && curr == 0) {
                im = i;
                cr = i - 3;
            }
            v.emplace_back(im);
            imposter[im] = 1;
            // if (ask(im, cr, i - 1) == 0) {

            // }
            for (int j = i + 1; j <= n; j++) {
                if (ask(im, cr, j) == 0) {
                    v.emplace_back(j);
                }
            }
            for (int j = 1; j <= 3; j++) {
                if (ask(j, j + 1, j + 3) == 0) {
                    for (int k = j; k <= i; k += 3) {
                        v.emplace_back(k);
                    }
                }
            }
            say();
            return;
        }
        last = curr;
    }

    for (int j = 1; j <= 3; j++) {
        if (ask(j, j + 1, j + 3) == 0) {
            for (int k = j; k <= n; k += 3) {
                v.emplace_back(k);
            }
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