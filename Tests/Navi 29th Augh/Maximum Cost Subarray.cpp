#include "bits/stdc++.h"
using namespace std;

void solve() {

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &i : a) cin >> i;

    for (int i = 1; i < n; i += 2) {
        a[i] = -a[i];
    }

    int mx = a[0], mn = a[0], cmx = a[0], cmn = a[0];
    for (int i = 1; i < n; i++) {
        cmx = max(a[i], cmx + a[i]);
        mx = max(mx, cmx);
        if (cmn > 0) {
            cmn = a[i];
        }
        else {
            cmn += a[i];
        }
        mn = min(mn, cmn);
    }

    int res = max(abs(mx), abs(mn));

    cout << res * res << '\n';
}


signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}