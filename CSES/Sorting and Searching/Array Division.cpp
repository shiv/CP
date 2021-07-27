/**
 *    author:  Shivam Gupta
 *    created: 17.07.2021 23:23:38
**/

#include "bits/stdc++.h"
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second;}
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "{"; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "}"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void out(bool ok, bool cap = true) { cap ? cout << (ok ? "YES" : "NO") : cout << (ok ? "Yes" : "No"); cout << "\n"; }
void print() { cout << "\n"; } template <typename Head> void print(Head H) { cout << H << "\n"; } template <typename Head, typename... Tail> void print(Head H, Tail... T) { cout << H << " "; print(T...); }
void dbg_out() { cerr << "\n"; } template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << " " << H; dbg_out(T...); }
#ifndef ONLINE_JUDGE
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug = true, dbg_out(__VA_ARGS__), debug = false
#else
#define dbg(...)
#endif

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 3e5 + 5;

void preSolve(int &t) {
}

void solve(int tc = 0) {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    cin >> x;

    int sum = accumulate(x.begin(), x.end(), (int)0);
    // int opt = max(*max_element(x.begin(), x.end()), (sum + k - 1) / k);
    int res = sum;
    int low = 1, high = sum;

    while (low <= high) {
        int mid = (low + high) >> 1;

        int curr = 0;
        int par = 1;
        for (int i = 0; i < n; i++) {
            if (x[i] > mid) {
                par = inf;
                break;
            }
            if (curr + x[i] <= mid) {
                curr += x[i];
            }
            else {
                par += 1;
                curr = x[i];
            }
        }

        if (par > k) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
            res = mid;
        }
    }

    print(res);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}