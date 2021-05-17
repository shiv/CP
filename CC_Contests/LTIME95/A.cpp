/**
 *    author:  Shivam Gupta
 *    created: 30.04.2021 19:29:46
**/

#include <bits/stdc++.h>
using namespace std;

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

// #undef _GLIBCXX_DEBUG
#define int             int64_t
#define vt              vector
#define vii             vector<int>
#define viii            vector<vector<int>>
#define pii             pair<int, int>
#define all(v)          (v).begin(), (v).end()
#define sz(v)           (int)(v).size()
#define pb              push_back
#define in              insert
#define F               first
#define S               second
#define inf             LLONG_MAX
#define For(i, a, b)    for (int i = (a); i < (b); i++)
#define Rev(i, a, b)    for (int i = (b - 1); i >= (a); i--)
#define Fore(i, a, b)   for (int i = (a); i <= (b); i++)
#define Reve(i, a, b)   for (int i = (b); i >= (a); i--)
#define memset(x, y)    memset(x, y, sizeof(x))
#define fps(x, y)       fixed << setprecision(y) << x
#define caseno(i)       cout << "Case #" << i << ": "
#define Time()          output << "[Execution : " << (1.0 * clock()) / CLOCKS_PER_SEC << "s]\n"

template <typename T, typename U> istream& operator>>(istream& in, pair<T, U>& a) { in >> a.F >> a.S; return in; }
template <typename T, typename U> ostream& operator<<(ostream& out, pair<T, U>& a) { out << a.F << " " << a.S; return out; }
template <typename T> istream& operator>>(istream& in, vector<T>& a) { for (T& x : a) in >> x; return in; }
template <typename T> ostream& operator<<(ostream& out, vector<T>& a) { bool f = false; for (T& x : a) { if (f) out << " "; out << x; f = true; } return out; }
template <typename T> ostream& operator<<(ostream& out, vector<vector<T>>& a) { for (vector<T>& x : a) out << x << '\n'; return out; }
template <typename A, size_t S> istream& operator>>(istream& in, array<A, S>& a) { for (A& x : a) in >> x; return in; }
template <typename A, size_t S> ostream& operator<<(ostream& out, array<A, S>& a) { bool f = false; for (A& x : a) { if (f) out << " "; out << x; f = true; } return out; }
template <typename A, size_t S, size_t T> ostream& operator<<(ostream& out, array<array<A, S>, T>& a) { for (array<A, S>& x : a) out << x << '\n'; return out; }
void out(bool ok, bool cap = true) { if (cap) cout << (ok ? "YES" : "NO") << '\n'; else cout << (ok ? "Yes" : "No") << '\n'; }

void print() { cout << '\n'; }
template <typename Head> void print(Head H) { cout << H; print(); }
template <typename Head, typename... Tail> void print(Head H, Tail... T) { cout << H << " "; print(T...); }

int rand_int(int l, int r) { static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count()); return uniform_int_distribution<int>(l, r)(gen); }
template <typename T> void myshuffle(vector<T> &a) { for (int i = 0; i < a.size(); i++) swap(a[i], a[rand_int(0, i)]); }

template <typename T, typename U> T amax(T& a, U b) { if (b > a) a = b; return a; }
template <typename T, typename U> T amin(T& a, U b) { if (b < a) a = b; return a; }

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

const int mod = 1000000007;
// const int mod = 998244353;

int largest_bit(int x) { return x==0 ? -1 : 63 - __builtin_clzll(x); }
int gcd(int a, int b) { if(a < b) return gcd(b, a); if (!b) return a; return gcd(b, a % b); }
int lcm(int a, int b) { return a / gcd(a, b) * b; }
int add(int a, int b) { a %= mod; b %= mod; a = (a + b) % mod; return a; }
int mul(int a, int b) { a %= mod; b %= mod; a = (a * b) % mod; return a; }
int sub(int a, int b) { a %= mod; b %= mod; a = ((a - b) % mod + mod) % mod; return a; }
int exp(int x, int y, int m = mod) { int res = 1; x = x % m; while (y > 0) { if (y & 1) res = (res * x) % m; y = y >> 1; x = (x * x) % m; } return res; }
int modinv(int x, int m = mod) { return exp(x, m - 2, m); }
vii primes(int n) { bool P[n + 1] = {false}; vii p; for (int j, i = 2; i <= n; i++) if (!P[i]) for (p.pb(i), j = i * i; j <= n; j += i) P[j] = true; return p; }
viii readGraph(int n, int m) { viii g(n); int a, b; for (int i = 0; i < m; i++) { cin >> a >> b; a--; b--; g[a].pb(b); g[b].pb(a); } return g; }

const int N = 3e5+5;

void preSolve(int &t) {
    cin >> t;
}

void solve(int tc = 0) {
    int n, k, a;
    cin >> n >> k >> a;
    vii f(k);
    cin >> f;
    viii g = readGraph(n, n - 1);

    a -= 1;
    vii depth(n, 0);
    vector<pii> down(n, {n, -1});

    vii special(n, 0);
    for (auto& i : f) {
    	i -= 1;
    	special[i] = 1;
    	down[i] = {0, i};
    }

    function<void (int)> dfs_Util;
    dfs_Util = [&] (int v) {
    	for (auto& u : g[v]) {
    		if (down[u].S != -1)
    			continue;
    		down[u] = {down[v].F + 1, down[v].S};
    		dfs_Util(u);
    	}
    };

    function<void (int, int)> dfs;
    dfs = [&] (int v, int w) {
    	for (auto& u : g[v]) {
    		if (u == w)
    			continue;
    		depth[u] = depth[v] + 1;
    		dfs(u, v);
    		amin(down[v], make_pair(down[u].F + 1, down[u].S));
    	}
    };

	dfs(a, -1);

	for (int i = 0; i < n; i++)
		if (down[i].S != -1)
			dfs_Util(i);

	vii max_val(n), node(n);
	For (i, 0, n) {
		if (down[i].S != -1) {
			node[i] = down[i].S;
			max_val[i] = depth[node[i]] - down[i].F;
		}
		else {
			node[i] = f[0];
			max_val[i] = -depth[i];
		}
	}

	for (auto& i : node)
		i += 1;

	print(max_val);
	print(node);
}

signed main() {
#ifdef DLOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}
