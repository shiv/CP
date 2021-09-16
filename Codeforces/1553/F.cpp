// chrono::system_clock::now().time_since_epoch().count()
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template <typename A, typename B> string to_string(pair<A, B> p);
string to_string(const char& ch) { return "'" + string(1, ch) + "'"; }
string to_string(const string& s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string((string) s); }
string to_string(bool b) { return (b ? "true" : "false"); }
string to_string(vector<bool> v) { bool first = true; string res = "{"; for (int i = 0; i < static_cast<int>(v.size()); i++) { if (!first) { res += ", "; } first = false; res += to_string(v[i]); } res += "}"; return res; }
template <typename A> string to_string(A v) { bool first = true; string res = "{"; for (const auto &x : v) { if (!first) { res += ", "; } first = false; res += to_string(x); } res += "}"; return res; }
template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
#define output cout
void debug_out() { output << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) { output << " " << to_string(H); debug_out(T...); }
#ifndef ONLINE_JUDGE
#define dbg(...) output << "[" << #__VA_ARGS__ << "] :", debug_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

template<int N> struct Fenw {
    ll t[N + 1];

    Fenw() {
        fill(t + 1, t + N + 1, 0ll);
    }

    void update(int p, ll x) {
        for (; p <= N; p |= (p + 1)) {
            t[p] += x;
        }
    }

    ll get(int p) {
        ll ret = 0;

        for (; p > 0; --p) {
            ret += t[p];
            p &= (p + 1);
        }

        return ret;
    }

    ll get(int l, int r) {
        return get(r) - get(l - 1);
    }
};

const int M = (int)3e5;

void solve() {
    int n;
    cin >> n;
    Fenw<M> A, B;
    ll pref = 0, ans = 0;

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        ans += x * (i - 1ll);
        ans += A.get(x);
        ans += pref;
        pref += x;

        for (int j = x; j <= M; j += x) {
            int l = j, r = min(M, j + x - 1);
            ans -= B.get(l, r) * j;
            A.update(l, -x);
        }

        B.update(x, 1);
        cout << ans << " \n"[i == n];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tt = 1;

    for (int i = 1; i <= tt; ++i) {
        solve();
    }

    return 0;
}