#include "bits/stdc++.h"
#include <cinttypes>
#include <cstdio>
#include <queue>
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second;}
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "{"; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "}"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void scan() {} template <typename Head, typename ...Tail> void scan(Head &H, Tail &...T) { cin >> H; scan(T...); }
void print() { cout << "\n"; } template <typename Head> void print(const Head &H) { cout << H << "\n"; } template <typename Head, typename ...Tail> void print(const Head &H, const Tail &...T) { cout << H << " "; print(T...); }
void dbg_out() { cerr << "\n"; } template <typename Head, typename ...Tail> void dbg_out(const Head &H, const Tail &...T) { cerr << " " << H; dbg_out(T...); }
#ifndef ONLINE_JUDGE
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug = true, dbg_out(__VA_ARGS__), debug = false
#else
#define dbg(...)
#endif

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

void solve() {

    int n;
    scan(n);
    string s;
    scan(s);

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = s[i] - '0';
    }

    vector<int> prev(n), next(n);
    for (int i = 0; i < n; i++) {
        prev[i] = i - 1;
        next[i] = i + 1;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i < n - 1; i++) {
        if ((v[next[i]] - v[i] + 10) % 10 == 1) {
            pq.emplace(v[i], i);
        }
    }

    while (true) {

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq_;

        while (!pq.empty()) {

            auto [i, idx] = pq.top();
            pq.pop();

            if (v[idx] == -1 || v[next[idx]] == -1 || (v[next[idx]] - v[idx] + 10) % 10 != 1 || v[idx] != i) {
                continue;
            }

            v[idx] = (v[idx] + 2) % 10;
            v[next[idx]] = -1;

            next[idx] = next[next[idx]];
            if (next[idx] != n) {
                prev[next[idx]] = idx;
            }

            if (prev[idx] != -1 && (v[idx] - v[prev[idx]] + 10) % 10 == 1) {
                if (v[prev[idx]] > i) {
                    pq.emplace(v[prev[idx]], prev[idx]);
                }
                else {
                    pq_.emplace(v[prev[idx]], prev[idx]);
                }
            }
            if (next[idx] != n && (v[next[idx]] - v[idx] + 10) % 10 == 1) {
                if (i < v[idx]) {
                    pq.emplace(v[idx], idx);
                }
                else {
                    pq_.emplace(v[idx], idx);
                }
            }
        }

        if (pq_.empty()) {
            break;
        }

        swap(pq, pq_);
    }

    string ans;
    int i = 0;
    do {
        ans += string(1, v[i] + '0');
        i = next[i];
    } while (i < n);

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