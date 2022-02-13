#include "bits/stdc++.h"
#include <valarray>
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

void solve() {

    int n;
    cin >> n;
    string s, x;
    cin >> s >> x;

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = s[i] - '0';
    }

    vector<vector<int>> rem(7, vector<int>(7, -1));
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            rem[(i * 10 + j) % 7][j] = i;
        }
    }

    vector<vector<int>> mem(n, vector<int>(7, -1));

    function<bool (int, int)> doit = [&] (int i, int r) {
        if (mem[i][r] != -1) {
            return mem[i][r];
        }
        bool tmp;
        if (i == 0) {
            tmp = r == 0;
        }
        else {
            int curr = rem[r][v[i - 1]], curr_z = rem[r][0];
            if (x[i - 1] == 'A') {
                for (int r = 0; r < 7; r++) {
                    if (r != curr && r != curr_z && doit(i - 1, r)) {
                        tmp = false;
                        break;
                    }
                }
                tmp = true;
            }
            else {
                tmp = doit(i - 1, curr) || doit(i - 1, curr_z);
            }
        }
        return mem[i][r] = tmp;
    };

    print(doit(n, 0) ? "T" : "A");
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