#include "bits/stdc++.h"
using namespace std;

// bool debug;
// template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &processes) { return is >> processes.first >> processes.second; }
// template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &processes) { return debug ? os << "(" << processes.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
// template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
// template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "["; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "]"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
// void scan() {} template <typename Head, typename ...Tail> void scan(Head &H, Tail &...T) { cin >> H; scan(T...); }
// void print() { cout << "\n"; } template <typename Head> void print(const Head &H) { cout << H << "\n"; } template <typename Head, typename ...Tail> void print(const Head &H, const Tail &...T) { cout << H << " "; print(T...); }
// template <typename Head> void dbg_out(string var, const Head &H) { cerr << var << " = " << H << endl; } template <typename Head, typename ...Tail> void dbg_out(string var, const Head &H, const Tail &...T) { for (int i = 0, b = 0; i < (int)var.size(); i++) { if (var[i] == '(' || var[i] == '{') b++; else if (var[i] == ')' || var[i] == '}') b--; else if (var[i] == ',' && b == 0) { cerr << var.substr(0, i) << " = " << H << " | "; dbg_out(var.substr(var.find_first_not_of(' ', i + 1)), T...); break; } } }
// #ifndef ONLINE_JUDGE
// #define dbg(...) debug = true, dbg_out(#__VA_ARGS__, __VA_ARGS__), debug = false
// #else
// #define dbg(...)
// #endif

// template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
// template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

// #define int int64_t
// const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

int findEarliestMonth(vector<int> stockPrice) {
    int64_t n = stockPrice.size();
    int64_t sum = accumulate(stockPrice.begin(), stockPrice.end(), 0LL);
    int64_t curr = 0;
    int64_t ans = 1e18;
    int64_t idx;
    for (int64_t i = 1; i < n; i++) {
        curr += stockPrice[i - 1];
        sum -= stockPrice[i - 1];
        int64_t d = abs(curr / i - sum / (n - i));
        if (d < ans) {
            ans = d;
            idx = i;
        }
    }
    return idx;
}

int minimizeMemory(vector<int> processes, int m) {
    int n = processes.size();
    int sum = accumulate(processes.begin() + m, processes.end(), 0LL);
    int res = sum;
    for (int i = m; i < n; i++) {
        sum += processes[i - m];
        sum -= processes[i];
        res = min(res, sum);
    }
    return res;
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cout << findEarliestMonth({1, 3, 2, 4, 5}) << endl;
    cout << findEarliestMonth({1, 1, 1, 1, 1, 1}) << endl;
    // cout << minimizeMemory({4, 6, 10, 8, 2, 1}, 3);
    // cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        // solve();
    }

    return 0;
}