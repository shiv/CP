#include <bits/stdc++.h>
using namespace std;

int ans = 0;

void dfs(int c, int p, int dist, vector<vector<int>> &adj, vector<int>& vals,
        multiset<int>& mx, map<int, int>& valcnt) {

    int pr = 0;
    if (valcnt.find(vals[c]) != valcnt.end()) {
        pr = valcnt[vals[c]];
    }
    if (pr) {
        mx.erase(mx.find(pr));
    }
    valcnt[vals[c]]++;
    mx.insert(valcnt[vals[c]]);

    if (*mx.rbegin() >= (dist + 1) / 2) {
        ans++;
    }

    for (auto &i : adj[c]) {
        if (i == p) continue;
        dfs(i, c, dist + 1, adj, vals, mx, valcnt);
    }

    int x = valcnt[vals[c]];
    valcnt[vals[c]]--;
    if (valcnt[vals[c]] == 0) valcnt.erase(vals[c]);
    mx.erase(mx.find(x));
    if (x > 1) {
        mx.insert(x - 1);
    }

}

void solve() {
    ans = 0;
    int n;
    cin >> n;
    vector<int> vals(n + 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i++) cin >> vals[i];

    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    multiset<int> mx;
    map<int, int> valcnt;
    dfs(1, 0, 1, adj, vals, mx, valcnt);
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}