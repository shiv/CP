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

int calculateProfit(vector<int> arr, int x, int y, int z) {

    const int N = 101, M = 21;
    int dp[M][M][M][N];
    int n = arr.size();
    memset(dp, -1, sizeof(dp));

    int ans = 0;
    function<int (int, int, int, int)> go = [&] (int x, int y, int z, int n) {
        if (dp[x][y][z][n] != -1) {
            return dp[x][y][z][n];
        }
        int tmp = 0;
        for (int i = 0; i < n; i++) {
            tmp = max(tmp, go(x, y, z, i));
        }
        if (n - 1 >= 0 && x >= 1) {
            tmp = max(tmp, go(x - 1, y, z, n - 1) + arr[n - 1]);
        }
        if (n - 2 >= 0 && y >= 1) {
            tmp = max(tmp, go(x, y - 1, z, n - 2) + arr[n - 1] + arr[n - 2]);
        }
        if (n - 3 >= 0 && z >= 1) {
            tmp = max(tmp, go(x, y, z - 1, n - 3) + arr[n - 1] + arr[n - 2] + arr[n - 3]);
        }
        ans = max(ans, tmp);
        return dp[x][y][z][n] = tmp;
    };

    go(x, y, z, n);

    return ans;
}

int main() {

    cout << calculateProfit({5, 3}, 1, 0, 0) << '\n';
    cout << calculateProfit({-6, -3, -3, 10}, 0, 0, 1) << '\n';
    cout << calculateProfit({-7, 4, 0, -7}, 0, 1, 0) << '\n';

    return 0;
}