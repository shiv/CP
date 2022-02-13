#include "bits/stdc++.h"
using namespace std;

#define int int64_t
void solve(int n, int x, vector<int> a, vector<int> b, int k) {

    int impressed, max_buildings;

    for (int low = 0, high = 1e9 + 1; high - low > 1; ) {
        int mid = (low + high) / 2;
        int tot = 0;
        for (int i = 0; i < n; i++) {
            tot += max<int>(0, b[i] * mid - a[i]);
        }
        if (tot <= x) {
            low = mid;
        }
        else {
            high = mid;
        }
        max_buildings = low;
    }

    impressed = max_buildings >= k;

    cout << impressed << ' ' << max_buildings << '\n';
}

signed main() {

    int n, x, k;
    cin >> n >> x >> k;
    vector<int> a(n), b(n);
    for (int &i : a) {
        cin >> i;
    }
    for (int &i : b) {
        cin >> i;
    }

    solve(n, x, a, b, k);

    return 0;
}