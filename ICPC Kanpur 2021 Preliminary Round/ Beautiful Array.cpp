#include "bits/stdc++.h"
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
    vector<int> a(n);
    scan(a);
    for (int &i : a) {
        --i;
    }

    if (n <= 2) {
        print(0);
        return;
    }

    if (n == 3) {
        print(a[0] == a[2]);
        return;
    }

    if (n == 4) {
        int res = 0;
        if (set<int>(a.begin(), a.end()).size() == 1) {
            print(2);
        }
        else if (a[0] == a[3] && a[0] != a[2] && a[1] != a[3]) {
            print(0);
        }
        else {
            print(1);
        }
        return;
    }

    const int M = 200;
    vector<vector<int>> mp(3, vector<int>(M + 6));
    vector<vector<int>> cn(3);
    vector<int> cc = a;
    vector<int> cnt(3);

    for (int i = 0; i < n; i++) {
        cnt[i % 3] += 1;
        mp[i % 3][a[i]] += 1;
        cn[i % 3].push_back(a[i]);
    }

    for (int i = 0; i < 3; i++) {
        sort(cn[i].begin(), cn[i].end());
        cn[i].erase(unique(cn[i].begin(), cn[i].end()), cn[i].end());
    }
        sort(cc.begin(), cc.end());
        cc.erase(unique(cc.begin(), cc.end()), cc.end());
        for (int i = 0; i < 2; i++) {
            cc.push_back(M + i);
        }

    for (int i = 0; i < 6; i++) {
        cn[i / 2].push_back(M + i);
    }

    int ans = inf;

    // for (auto &c0 : cn[0]) {
    //     for (auto &c1 : cn[1]) {
    //         for (auto &c2 : cn[2]) {
    for (auto &c0 : cc) {
        for (auto &c1 : cc) {
            for (auto &c2 : cc) {
                vector<int> c = {c0, c1, c2};
                if (c[0] == c[1] || c[1] == c[2] || c[2] == c[0]) {
                    continue;
                }
                int res = 0;
                vector<int> r(3);
                for (int i = 0; i < 3; i++) {
                    r[i] = cnt[i] - mp[i][c[i]];
                    res += r[i];
                }
                {
                    int rm = inf;
                    for (int i = 0; i < 3; i++) {
                        int j = (i + 1) % 3;
                        rm = min(rm, mp[i][c[j]]);
                        rm = min(rm, r[i]);
                    }
                    for (int i = 0; i < 3; i++) {
                        r[i] -= rm;
                    }
                    res -= rm;
                }
                {
                    int rm = inf;
                    for (int i = 0; i < 3; i++) {
                        int j = (i + 2) % 3;
                        rm = min(rm, mp[i][c[j]]);
                        rm = min(rm, r[i]);
                    }
                    for (int i = 0; i < 3; i++) {
                        r[i] -= rm;
                    }
                    res -= rm;
                }
                for (int i = 0; i < 3; i++) {
                    int j = (i + 1) % 3;
                    int rm = min({mp[i][c[j]], mp[j][c[i]], r[i], r[j]});
                    r[i] -= rm;
                    r[j] -= rm;
                    res -= rm;
                }
                // auto rr = r;
                ans = min(ans, res);
            }
        }
    }

    // vector<int> c(3);
    // for (c[0] = 0; c[0] < M; c[0]++) {
    //     for (c[1] = 0; c[1] < M; c[1]++) {
    //         for (c[2] = 0; c[2] < M; c[2]++) {
    //             if (c[0] == c[1] || c[1] == c[2] || c[2] == c[0]) {
    //                 continue;
    //             }
    //             int res = 0;
    //             for (int i = 0; i < 3; i++) {
    //                 res += cnt[i] - mp[i][c[i]];
    //             }
    //             for (int i = 0; i < 3; i++) {
    //                 int j = (i + 1) % 3;
    //                 res -= min(mp[i][c[j]], mp[j][c[i]]);
    //             }
    //             ans = min(ans, res);
    //         }
    //     }
    // }

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