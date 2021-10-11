#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
// #pragma GCC target ("sse4")
using namespace std;

#define  prin   for (int i = 0; i < 1 << b; i++) { for (int j = 0; j <= c; j++) { cout << dp[i][j] << " \n"[j == c];  } }

int main() {
#define int int64_t
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int b, c;
    cin >> c >> b;

    int time[b][c + 1];
    for (int i = 0; i < b; i++) {
        time[i][0] = 0;
        for (int j = 1; j <= c; j++) {
            cin >> time[i][j];
            time[i][j] += time[i][j - 1];
        }
    }

    int b_ = 1 << b;
    int dp[b_][c + 1];
    for (int i = 0; i < b_; i++) {
        for (int j = 0; j <= c; j++) {
            dp[i][j] = 1e9;
        }
    }
    for (int i = 0; i < b; i++) {
        for (int idx = 1 << i, j = 0; j <= c; j++) {
            dp[idx][j] = time[i][j];
        }
    }
    prin;

    int ans = 1e9;

    for (int m = 1; m < b_; m++) {
        for (int x = 0; x < b; x++) {
            if (!(m & (1 << x))) {
                for (int y = 1; y <= c; y++) {
                    for (int z = y; z <= c; z++) {
                        int idx = m | 1 << x;
                        dp[idx][z] = min(dp[idx][z], dp[m][y - 1] - time[x][y - 1] + time[x][z]);
                        dp[idx][z] = min(dp[idx][z], dp[m][z]);
                    }
                }
            }
        }
        ans = dp[m][c];
        // ans = min(ans, dp[m][c]);
    }
    prin;


    cout << ans;

    return 0;
}