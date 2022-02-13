#include "bits/stdc++.h"
using namespace std;

#define int int64_t
const int inf =  1e9 + 5;

class segtree {
public:
    struct node {

        int val = inf;
        int lazy = -1;

        void apply(int l, int r, int v) {
            val = v;
        }
    };

    node unite(const node &a, const node &b) const {
        node res;
        res.val = min(a.val, b.val);
        return res;
    }

    inline void push(int x, int l, int r) {
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        if (tree[x].lazy != node().lazy) {
            tree[x + 1].apply(l, y, tree[x].lazy);
            tree[z].apply(y + 1, r, tree[x].lazy);
            tree[x].lazy = node().lazy;
        }
    }

    inline void pull(int x, int z) {
        tree[x] = unite(tree[x + 1], tree[z]);
    }

    int n;
    vector<node> tree;

    void build(int x, int l, int r) {
        if (l == r) {
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y);
        build(z, y + 1, r);
        pull(x, z);
    }

    node get(int x, int l, int r, int ll, int rr) {
        if (ll <= l && r <= rr) {
            return tree[x];
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        node res;
        if (rr <= y) {
            res = get(x + 1, l, y, ll, rr);
        }
        else {
            if (ll > y) {
                res = get(z, y + 1, r, ll, rr);
            }
            else {
                res = unite(get(x + 1, l, y, ll, rr), get(z, y + 1, r, ll, rr));
            }
        }
        pull(x, z);
        return res;
    }

    template <typename... M>
    void modify(int x, int l, int r, int ll, int rr, const M&... v) {
        if (ll <= l && r <= rr) {
            tree[x].apply(l, r, v...);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        if (ll <= y) {
            modify(x + 1, l, y, ll, rr, v...);
        }
        if (rr > y) {
            modify(z, y + 1, r, ll, rr, v...);
        }
        pull(x, z);
    }

    segtree(int _n) : n(_n) {
        assert(n > 0);
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }

    node get(int ll, int rr) {
        return get(0, 0, n - 1, ll, rr);
    }

    node get(int p) {
        return get(0, 0, n - 1, p, p);
    }

    template <typename... M>
    void modify(int ll, int rr, const M&... v) {
        modify(0, 0, n - 1, ll, rr, v...);
    }
};

int solve(int n, int m, vector<vector<int>> a) {

    sort(a.begin(), a.end(), [&] (auto &x, auto &y) {
        if (x[1] == y[1]) {
            return x < y;
        }
        return x[1] < y[1];
    });

    segtree seg(n);
    vector<int> dp(n, inf);
    dp[0] = 0;
    seg.modify(0, 0, 0);

    for (auto &p : a) {
        int u = p[0] - 1;
        int v = p[1] - 1;
        int w = p[2];
        dp[v] = min(dp[v], seg.get(u, v - 1).val + w);
        seg.modify(v, v, dp[v]);
    }

    int ans = seg.get(n - 1).val;
    ans = ans == inf ? -1 : ans;

    return ans;
}

signed main() {

    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(m, vector<int>(3));
    for (int i = 0; i < m; i++) {
        cin >> v[i][0] >> v[i][1] >> v[i][2];
    }

    cout << solve(n, m, v);

    return 0;
}