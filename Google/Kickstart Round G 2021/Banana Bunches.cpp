#include "bits/stdc++.h"
#include <cinttypes>
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

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

void solve() {

    int n, k;
    scan(n, k);
    vector<int> b(n);
    scan(b);

    vector<int64_t> pref(n);
    for (int i = 0; i < n; i++) {
        pref[i] = b[i];
    }
    for (int i = 1; i < n; i++) {
        pref[i] += pref[i - 1];
    }
    const int MAX = k + 5;
    int len[MAX];
    memset(len, -1, sizeof(len));
    int ans = n + 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j >= 0; j--) {
            auto currSum = pref[i] - pref[j] + b[j];
            if (currSum == k) {
                amin(ans, i - j + 1);
            }
            else if (currSum < k && ~len[k - currSum]) {
                amin(ans, i - j + 1 + len[k - currSum]);
            }
        }
        for (int j = n - 1; j >= i; j--) {
            auto currSum = pref[j] - pref[i] + b[i];
            if (currSum <= k && (len[currSum] == -1 || j - i + 1 < len[currSum])) {
                len[currSum] = j - i + 1;
            }
        }
    }
    print(ans > n ? -1 : ans);
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