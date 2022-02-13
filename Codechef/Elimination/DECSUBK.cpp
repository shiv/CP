#include "bits/stdc++.h"
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

int lis(vector<int> arr) {
    int n = arr.size();
    int lis[n];

    lis[0] = 1;

    for (int i = 1; i < n; i++) {
        lis[i] = 1;
        for (int j = 0; j < i; j++)
            if (arr[i] >= arr[j] && lis[i] < lis[j] + 1)
                lis[i] = lis[j] + 1;
    }

    return *max_element(lis, lis + n);
}

void solve() {

    int n, k;
    scan(n, k);
    vector<int> a(n);
    scan(a);

    sort(a.begin(), a.end());

    int idx = -1;
    bool ok = true;
    for (int i = n - 1; i >= 0; i--) {
        auto b = a;
        reverse(b.begin() + i, b.end());
        if (lis(b) == k) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        print(-1);
        return;
    }

    pair<int, int> high_freq(-1, -1);
    {
        map<int, int> mp;
        for (int i = idx; i < n; i++) {
            mp[a[i]] += 1;
        }

        for (auto &[ele, freq] : mp) {
            high_freq = max(high_freq, {freq, -ele});
        }
    }
    auto [freq, ele] = high_freq;
    ele = -ele;

    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < n; i++) {
        if (i >= idx && a[i] != ele) {
            pq.emplace(a[i]);
        }
    }

    vector<int> b;
    for (int i = 0; i < idx; i++) {
        b.emplace_back(a[i]);
    }

    while (!pq.empty() && freq > 1) {
        b.emplace_back(ele);
        b.emplace_back(pq.top());
        pq.pop();
        freq -= 1;
    }

    vector<int> c;
    while (!pq.empty()) {
        c.emplace_back(pq.top());
        pq.pop();
    }
    for (int i = 0; i < freq; i++) {
        c.emplace_back(ele);
    }
    sort(c.begin(), c.end(), greater<int>());
    b.insert(b.end(), c.begin(), c.end());

    print(b);
}
// 1 2 3 4 5 6 7 8 8 9 10
// 1 2 3 4 5 10 9 8 8 7 6
// 1 2 3 4 5 8 6 10 9 8 7

// 1 2 3 4 5 6 7 8 8 8 9 10
// 1 2 3 4 5 10 9 8 8 8 7 6
// 1 2 3 4 5 8 6 8 7 10 9 8

// 1 2 3 4 5 6 7 8 8 8 8 8 9 10
// 1 2 3 4 5 10 9 8 8 8 8 8 7 6
// 1 2 3 4 5 8 6 8 7 8 9 8 10 8
signed main() {
// 1 2 3 4 5 6 7
// 1 2 7 6 5 4 3
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}
/*
int high_freq = -1;

    map<int, int> mp;
    for (int &i : a) {
        mp[i] += 1;
    }

    for (auto &[ele, freq] : mp) {
        amax(high_freq, freq);
    }

    if (high_freq > k) {
        print(-1);
        return;
    }
*/