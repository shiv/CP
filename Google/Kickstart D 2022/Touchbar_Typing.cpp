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
    int m;
    scan(m);
    vector<int> b(m);
    scan(b);

    const int M = 2500 + 5;

    vector<vector<int>> idx(M);
    for (int i = 0; i < m; i++) {
        idx[b[i]].emplace_back(i);
    }

    int k = idx[a[0]].size();
    vector<int> dp(k);

    for (int i = 1; i < n; i++) {

        int prev = a[i - 1];
        int curr = a[i];

        auto preprocess = [&] (int beg, int end) {
            vector<int> vec;
            int x = beg, mn = inf;
            for (int j = beg; beg < end ? j <= end : j >= end; beg < end ? j++ : j--) {
                mn += abs(idx[prev][j] - x);
                amin(mn, dp[j]);
                vec.emplace_back(mn);
                x = idx[prev][j];
            }
            return vec;
        };
        auto left = preprocess(0, int(idx[prev].size()) - 1);
        auto right = preprocess(int(idx[prev].size()) - 1, 0);

        vector<int> new_dp(idx[curr].size(), inf);
        auto check = [&] (int j, int k) {
            if (j >= 0 && j < idx[prev].size()) {
                amin(new_dp[k], dp[j] + abs(idx[curr][k] - idx[prev][j]));
            }
        };

        for (int k = 0; k < idx[curr].size(); k++) {
            int j = lower_bound(idx[prev].begin(), idx[prev].end(), idx[curr][k]) - idx[prev].begin();
            check(j, k);
            check(j - 1, k);
        }

        swap(dp, new_dp);
    }

    int ans = *min_element(dp.begin(), dp.end());
    print(ans);
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}