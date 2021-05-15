#include <bits/stdc++.h>
using namespace std;

#define int             long long
#define vii             vector<int>
#define viii            vector<vector<int>>
#define pii             pair<int, int>
#define all(v)          (v).begin(), (v).end()
#define sz(v)           (int)(v).size()
#define pb              push_back
#define F               first
#define S               second
#define For(i, a, b)    for (int i = a; i < b; i++)

const int mod = 1000000007;

void presolve(int &t) {
    cin >> t;
}

void solve() {
    int n, m;
    cin >> n >> m;
    
    int ans = 0;
    int o = min(n, m);
    vii a(o + 1);
    for (int i = 1; i <= o; i++) {
        ans += a[m % i];
        for (int j = m % i; j <= o; j += i)
            a[j]++;
    }
    for (int i = o + 1; i <= n; i++)
        ans += i - 1;
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    presolve(t);
    for (int i = 1; i <= t; i++)
        solve();
    return 0;
}
