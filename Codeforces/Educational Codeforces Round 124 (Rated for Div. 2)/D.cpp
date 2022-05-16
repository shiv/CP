#include "bits/stdc++.h"
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second; }
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "["; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "]"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void scan() {} template <typename Head, typename ...Tail> void scan(Head &H, Tail &...T) { cin >> H; scan(T...); }
void print() { cout << "\n"; } template <typename Head> void print(const Head &H) { cout << H << "\n"; } template <typename Head, typename ...Tail> void print(const Head &H, const Tail &...T) { cout << H << " "; print(T...); }
template <typename Head> void dbg_out(string var, const Head &H) { cerr << var << " = " << H << endl; } template <typename Head, typename ...Tail> void dbg_out(string var, const Head &H, const Tail &...T) { for (int i = 0, b = 0; i < (int)var.size(); i++) { if (var[i] == '(' || var[i] == '{') b++; else if (var[i] == ')' || var[i] == '}') b--; else if (var[i] == ',' && b == 0) { cerr << var.substr(0, i) << " = " << H << " | "; dbg_out(var.substr(var.find_first_not_of(' ', i + 1)), T...); break; } } }
#ifndef ONLINE_JUDGE
#define dbg(...) debug = true, dbg_out(#__VA_ARGS__, __VA_ARGS__), debug = false
#else
#define dbg(...)
#endif

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

struct Point {
    int x, y;
    friend istream& operator>>(istream& in, Point &n) {
        return in >> n.x >> n.y;
    }
    friend ostream& operator<<(ostream& out, const Point &n) {
        return out << n.x << ' ' << n.y;
    }
};

// functions: set.insert(val), *(set.find_by_order(order-1)), set.order_of_key(val)
// less_equal for multiset

void solve() {

    int n;
    scan(n);
    vector<Point> a(n);
    scan(a);

    auto isValid = [&] (int x) {
        return 1 <= x && x <= n;
    };


    vector<oset<int>> rows(N), columns(N);
    set<int> s;

    auto hash = [&] (int x, int y) {
        return x * N + y;
    };

    vector<vector<int>> mat(10, vector<int>(10));
    for (auto &p : a) {
        mat[p.x][p.y] = 1;
        s.emplace(hash(p.x, p.y));
        rows[p.x].insert(p.y);
        columns[p.y].insert(p.x);
    }
    // for (auto x : mat) {
    //     print(x);
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            cout << mat[i][j] << " \n"[j == 9];
        }
    }
    // }
    pair<int, int> ans(-1, -1);

    for (auto &p : a) {
        auto [x, y] = p;
        int i = 0;
        while (++i) {
            int lx = x - i, rx = x + i, ly = y - i, ry = y + i;
            bool ok = isValid(lx) && isValid(rx) && isValid(ly) && isValid(ry);
            if (!ok) break;
            ok &= rows[rx].order_of_key(ry + 1) - rows[rx].order_of_key(ly) == i * 2 + 1;
            ok &= rows[lx].order_of_key(ry + 1) - rows[lx].order_of_key(ly) == i * 2 + 1;
            ok &= columns[ry].order_of_key(rx + 1) - columns[ry].order_of_key(lx) == i * 2 + 1;
            ok &= columns[ly].order_of_key(rx + 1) - columns[ly].order_of_key(lx) == i * 2 + 1;
            if (!ok) break;
        }
        if (y - i >= 1) {
            for (int j = max<int>(1, x - i); j <= x + i; j++) {
                if (s.find(hash(j, y - i)) == s.end()) {
                    ans = {j, y - i};
                }
                if (s.find(hash(j, y + i)) == s.end()) {
                    ans = {j, y + i};
                }
            }
        }
        if (x - i >= 1) {
            for (int j = max<int>(1, y - i); j <= y + i; j++) {
                if (s.find(hash(x - i, j)) == s.end()) {
                    ans = {x - i, j};
                }
                if (s.find(hash(x + i, j)) == s.end()) {
                    ans = {x + i, j};
                }
            }
        }
        print(ans.first, ans.second);
    }
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