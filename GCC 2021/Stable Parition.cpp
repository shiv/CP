#include <bits/stdc++.h>
using namespace std;

#define int int64_t
const int mod = 1e9 + 7;

struct dsu {
  public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    vector<vector<int>> groups() {
        vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(remove_if(result.begin(), result.end(), [&](const vector<int>& v) { return v.empty(); }), result.end());
        return result;
    }

  private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    vector<int> parent_or_size;
};

const int X = 1e6 + 10, inf = 1e9;
int lp[X];

vector<int> factor(int x) {
    vector<int> res;
    while (x != 1) {
        int y = lp[x];
        while (x % y == 0) x /= y;
        res.push_back(y);
    }
    return res;
}

int same[X];

int power(int a, int b){
    int res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void solve() {

    int n;
    cin >> n;
    vector<int> r(n);
    for (auto &x : r) {
        cin >> x;
    }

    dsu g(n);

    for (int i = 0; i < n; i++) {
        auto f = factor(r[i]);
        for (auto p : f) {
            if (same[p] < 0)
                same[p] = i;
            else
                g.merge(i, same[p]);
        }
    }

    int ans = 0;

    auto groups = g.groups().size();

    if (groups == 1) {
        cout << "NO\n0";
    }
    else {
        cout << "YES\n";
        int ans = power(2, groups);
        ans = (ans + mod - 2) % mod;
        cout << ans;
    }
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    lp[1] = inf;
    for (int p = 2; p < X; ++p) {
        if (lp[p] != 0) continue;
        for (int d = p; d < X; d += p)
            if (lp[d] == 0)
                lp[d] = p;
    }

    fill_n(same, X, -1);

    solve();
}