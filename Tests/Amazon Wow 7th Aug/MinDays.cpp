#include "bits/stdc++.h"
using namespace std;

vector<int> primes(int k) {
    int n = 1e7;
    static bool ok = false;
    static vector<bool> P(n + 1, false);
    static vector<int> p;
    if (!ok) {
        for (long long i = 2; i <= n; i++) {
            if (!P[i]) {
                p.push_back(i);
                for (long long j = i * i; j <= n; j += i)  {
                    P[j] = true;
                }
            }
        }
        ok = true;
    }
    return vector<int>(p.begin(), p.begin() + k);
}

int minDays(int d, int k) {
    vector<int> prime = primes(k);
    vector<int> dp(d + 1, 1e9);
    dp[0] = 0;

    for (auto& c : prime) {
        for (int i = 0; i <= d; i++) {
            if (i - c >= 0) {
                dp[i] = min(dp[i], dp[i - c] + 1);
            }
        }
    }
    return dp[d] == 1e9 ? -1 : dp[d];
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        // solve();
        cout << minDays(10, 1) << endl;
        cout << minDays(11, 3) << endl;
        cout << minDays(1, 3) << endl;
    }

    return 0;
}