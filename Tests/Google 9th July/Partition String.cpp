#include <bits/stdc++.h>
using namespace std;

int main() {
    const int mod = 1e9 + 7;
    int n, m, k;
    string s;
    cin >> n >> m >> k >> s;
    vector<vector<int>> dp(2001, vector<int>(2001));
    if ((s[0] - '0') % 2 || (s[n - 1] - '0') % 2 == 0) {
        cout << "0\n";
        return 0;
    }
    vector<bool> v(n, 0);
    v[n - 1] = 1;
    dp[n][1] = 1;
    for (int i = 1; i < n - 1; i++) {
        if ((s[i] - '0') % 2 && (s[i + 1] - '0') % 2 == 0) {
            v[i] = 1;
        }
    }
    for (int i = 0; i <= n; i++) dp[i][0] = 1;
    for (int i = n - 1 - m ; i >= m - 1 ; i--) {
        dp[i] = dp[i + 1];
        if (v[i]) {
                for (int j = 1; j <= k; j++) {
                if (i + m <= n) (dp[i][j] += dp[i + m][j - 1]) %= mod;
            }
        }
    }
    cout << dp[m - 1][k - 1] << '\n';
    return 0;
}