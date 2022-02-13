#include "bits/stdc++.h"
using namespace std;

void solve() {

    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> v;
    v.emplace_back(0, 1);
    v.emplace_back(1, 2);

    for (int i = 2; i <= n; i++) {
        for (int j = v.size() - 2; j >= 0; j--) {
            int a = j, b = j + 1;
            if (v[a].second + v[b].second <= i) {
                v.insert(v.begin() + j + 1, {v[a].first + v[b].first, v[a].second + v[b].second});
            }
        }
    }

    cout << v[k - 1].first << "/" << v[k - 1].second;
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}