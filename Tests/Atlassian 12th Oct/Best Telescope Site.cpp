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

int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < edges.size(); i++) {
        dp[edges[i][0]][edges[i][1]] = edges[i][2];
        dp[edges[i][1]][edges[i][0]] = edges[i][2];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (dp[j][i] != INT_MAX && dp[i][k] != INT_MAX)
                    dp[j][k] = min(dp[j][k], (dp[j][i] + dp[i][k]));
            }
        }
    }
    int ma = INT_MAX;
    int ans;
    for (int i = 0; i < n; i++)
    {
        int c = 0;
        for (int j = 0; j < n; j++)
            if (i != j && dp[i][j] <= distanceThreshold)
                c++;
        if (ma >= c)
        {
            ma = c;
            ans = i;
        }
    }
    return ans;
}
int findBestCity(int d, int n, vector<int> c_f, vector<int> c_t, vector<int> c_w) {
    int nn = c_f.size();
    vector<vector<int>> edges(nn);
    for (int i = 0; i < nn; i++) {
        edges[i] = {c_f[i] - 1, c_t[i] - 1, c_w[i]};
    }
    return findTheCity(n, edges, d);
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;

    for (int tt = 1; tt <= t; tt++) {
        cout << findBestCity(1, 4, {1, 1, 1, 2, 2, 3}, {2, 3, 4, 3, 4, 4}, {1, 3, 2, 1, 1, 1});
    }

    return 0;
}