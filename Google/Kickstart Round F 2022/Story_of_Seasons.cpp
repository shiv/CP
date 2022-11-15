#include "bits/stdc++.h"
using namespace std;

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

struct plant {
    int q, l, v;
};

void solve() {

    int d, n, x;
    scan(d, n, x);
    vector<plant> pp(n);
    for (auto &p : pp) {
        cin >> p.q >> p.l >> p.v;
    }

    map<pair<int, int>, int> mp;
    mp[{1, d}] = x;

    sort(pp.begin(), pp.end(), [&] (auto &a, auto &b) {
        if (a.v == b.v) return a.l < b.l;
        return a.v > b.v;
    });

    int ans = 0;

    for (auto &p : pp) {

        int ex = d - p.l;
        // auto curr = mp.upper_bound({ex, ex});
        // auto curr = mp.upper_bound(ex, [&] (auto p) {
        //     return p.first <= ex;
        // });

        while (p.q > 0) {

            auto curr = mp.lower_bound({ex + 1, -inf});
            // dbg(mp, ex, *curr);
            if (curr == mp.begin()) {
                break;
            }
            curr = prev(curr);
            // if (curr->first.second < ex) {
            //     if (curr == mp.begin()) break;
            //     curr = prev(curr);
            // }
            // dbg(*curr, mp);
            // dbg(1);

            if (curr->first.first == curr->first.second) {
                int used = min(p.q, curr->second);
                ans += used * p.v;
                p.q -= used;
                curr->second -= used;
                if (curr->second == 0) {
                    mp.erase(curr);
                }
            }
            else {
                int tot = (ex - curr->first.first + 1) * x;
                // dbg(tot, p.q);
                if (tot <= p.q) {
                    // dbg(ex);
                    ans += tot * p.v;
                    p.q -= tot;
                    if (ex != curr->first.second) {
                        mp[{ex + 1, curr->first.second}] = x;
                    }
                    mp.erase(curr);
                }
                else {
                    ans += p.q * p.v;
                    if (ex != curr->first.second) {
                        mp[{ex + 1, curr->first.second}] = x;
                    }
                    int rem = tot - p.q;
                    int start = curr->first.first;
                    int end = start + rem / x - 1;
                    // dbg(tot, rem, p.q);
                    if (rem >= x) {
                        mp[{start, end}] = x;
                    }
                    if (rem % x != 0) {
                        mp[{end + 1, end + 1}] = rem % x;
                    }
                    p.q = 0;
                    mp.erase(curr);
                }
            }
            // int used = min(p.q, curr->second);
            // ans += used * p.v;
            // p.q -= used;
            // curr->second -= used;
            // if (curr->second == 0) {
            // }
        }

    }

    print(ans);
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}