#include <bits/stdc++.h>
using namespace std;

string to_string(const char& ch) { return "'" + string(1, ch) + "'"; }
string to_string(const string& s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string((string) s); }
string to_string(bool b) { return (b ? "true" : "false"); }
string to_string(vector<bool> v) { bool first = true; string res = "{"; for (int i = 0; i < static_cast<int>(v.size()); i++) { if (!first) { res += ", "; } first = false; res += to_string(v[i]); } res += "}"; return res; }
template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename A> string to_string(A v) { bool first = true; string res = "{"; for (const auto &x : v) { if (!first) { res += ", "; } first = false; res += to_string(x); } res += "}"; return res; }
#define output cout
void debug_out() { output << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) { output << " " << to_string(H); debug_out(T...); }
#ifndef ONLINE_JUDGE
#define dbg(...) output << "[" << #__VA_ARGS__ << "] :", debug_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

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
	string s;
	cin >> s;

    int n = s.size();
    vii a(n);
    for (int i = 0; i < n; i++)
        a[n - i - 1] = s[i] - '0';

    if (accumulate(all(a), 0ll) == n) {
        cout << 0 << '\n';
        return;
    }

    for (int i = 1; i < 1 << n; i++) {
        int j = i, k = 0;
        while (k < n && j != 0) {
            if (a[k] == (j & 1))
                j >>= 1;
            k++;
        }
        if(j != 0) {
            vii v;
            while (i != 0) {
                v.push_back(i & 1);
                i >>= 1;
            }
            reverse(all(v));
            for (auto ch : v)
                cout << ch;
            cout << '\n';
            return;
        }
    }
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