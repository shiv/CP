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
	int n;
    cin >> n;
	
    int ans = 0;

	if (n == 1)
		ans = 20;
	if (n == 2)
		ans = 36;
	if (n == 3)
		ans = 51;
	if (n >= 4) {
		int rem = n % 4;
		ans = n / 4 * 44;
		ans += (4 - rem) * 4;
		if (rem == 1)
			ans += 20;
		if (rem == 2)
			ans += 36;
		if (rem == 3)
			ans += 51;
	}

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