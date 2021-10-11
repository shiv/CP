#include "bits/stdc++.h"
using namespace std;

#define int int64_t
const int N = 32000;

vector<bool> prime(N, true);
vector<int> primes;
void sieve() {
    for(int i = 2; i < N; i++) {
        if (prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j < N; j += i) {
                prime[j] = false;
            }
        }
    }
}

void solve() {

    int a, b;
    cin >> a >> b;

    auto check = [&] (int n) {

        for (auto &i : primes) {

            while (n % i == 0) {

                n /= i;

                if (b % n == 0) {
                    return true;
                }

                if (b % i != 0) {
                    return false;
                }
            }
        }

        return b % n == 0;
    };

    cout << (check(a) ? "YES\n" : "NO\n");
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    sieve();

    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}