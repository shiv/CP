/**
 *    author:  Shivam Gupta
 *    created: 18.04.2021 22:02:58
**/

// #undef _GLIBCXX_DEBUG
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

#define FASTIO          ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define int             long long
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
#define Reve(i, a, b)    for (int i = (b); i >= (a); i--)
#define memset(x, y)    memset(x, y, sizeof(x))
#define fps(x, y)       fixed << setprecision(y) << x
#define caseno(i)       cout << "Case #" << i << ": "
#define Time()          cerr << "[Execution : " << (1.0 * clock()) / CLOCKS_PER_SEC << "s]\n"

template <typename T, typename U> istream& operator>>(istream& in, pair<T, U>& a) { in >> a.F >> a.S; return in; }
template <typename T, typename U> ostream& operator<<(ostream& out, pair<T, U>& a) { out << a.F << " " << a.S; return out; }
template <typename T> istream& operator>>(istream& in, vector<T>& a) { for (T& x : a) in >> x; return in; }
template <typename T> ostream& operator<<(ostream& out, vector<T>& a) { bool f = false; for (T& x : a) { if (f) out << " "; out << x; f = true; } out << '\n'; return out; }
void out(bool ok, bool cap = true) { if (cap) cout << (ok ? "YES" : "NO") << '\n'; else cout << (ok ? "Yes" : "No") << '\n'; }

void pr() {}
void print() { cout << '\n'; }
template <typename Head, typename... Tail> void pr(Head H, Tail... T) { cout << H << " "; pr(T...); }
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

vii primes(int n) { bool P[n + 1] = {false}; vii p; for (int j, i = 2; i <= n; i++) if (!P[i]) for (p.pb(i), j = i * i; j <= n; j += i) P[j] = true; return p; }
int largest_bit(int x) { return x==0 ? -1 : 63 - __builtin_clzll(x); }
int gcd(int a, int b) { if(a < b) return gcd(b, a); if (!b) return a; return gcd(b, a % b); }
int lcm(int a, int b) { return a / gcd(a, b) * b; }
int add(int a, int b) { a %= mod; b %= mod; a = (a + b) % mod; return a; }
int mul(int a, int b) { a %= mod; b %= mod; a = (a * b) % mod; return a; }
int sub(int a, int b) { a %= mod; b %= mod; a = ((a - b) % mod + mod) % mod; return a; }
int exp(int x, int y, int m = mod) { int res = 1; x = x % m; while (y > 0) { if (y & 1) res = (res * x) % m; y = y >> 1; x = (x * x) % m; } return res; }
int modinv(int x, int m = mod) { return exp(x, m - 2, m); }
viii readGraph(int n, int m) { viii g(n); int a, b; for (int i = 0; i < m; i++) { cin >> a >> b; a--; b--; g[a].pb(b); g[b].pb(a); } return g; }

const int N = 3e5+5;

void preSolve(int &t) {
    // cin >> t;
}

#define ll int64_t

struct segtree {
    ll N=0;
    vii seg, a;
    
    void init(ll n) {
		N=pow(2,ceil(log2(n)));
		seg.resize(2*N);
		a.resize(N);
    }
    
    void build(ll i=0, ll l=0, ll r=0) {
        if(i==0) i=1, l=0, r=N;
        if(r-l==1) {
          seg[i]=a[l];
          return;
        }
        ll m=(l+r)/2;
        build(i*2, l, m);
        build(i*2+1, m, r);
        seg[i]=seg[i*2]+seg[i*2+1];
    }
    
    void Set(ll pos, ll val, ll i=0, ll l=0, ll r=0) {
        if(i==0) i=1, l=0, r=N;
        // pr(i);
        if(r-l==1) {
            seg[i]=val;
            return;
        }
        ll m=(l+r)/2;
        if(pos<m) Set(pos, val, i*2, l, m);
        else Set(pos, val, i*2+1, m, r);
        seg[i]=seg[i*2]+seg[i*2+1];
    }
    
    ll calc(ll lx, ll rx=0, ll i=0, ll l=0, ll r=0) {
        if(i==0) i=1, l=0, r=N, rx=N;
        if(min(rx,r)<=max(l,lx)) return 0;
        if(lx<=l&&r<=rx) return seg[i];
        ll m=(l+r)/2;
        return calc(lx, rx, i*2, l, m) + calc(lx, rx, i*2+1, m, r);
    }
    
    
};

struct SegTree {
	typedef int T;
    int n;
	vector<T> val;
	static constexpr T unit = INT_MIN;
	SegTree(int n = 0, T def = unit, vector<T> &a) : val(4 * n, def), n(n), a(a) {}

	T merge(T a, T b) { 
		return max(a, b); 
	}
 
    void build(int x, int lx, int rx) {
        if (rx - lx == 1)
        	return s[x] = a[lx];
        int mid = (lx + rx)/2;
        build(a, 2*x + 1, lx, mid);
        build(a, 2*x + 2, mid, rx);
        val[x] = merge(val[2*x + 1], val[2*x + 2]);
    }

    void build() {
    	build(1, 0, n);
    }
 
    void build(vector<int> &a) {
        build(a, 0, 0, N);
    }
 
    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) return void(values[x] = single(v));
        int mid = (lx + rx)/2;
        if (i < mid) {
            set(i, v, 2*x + 1, lx, mid);
        } else {
            set(i, v, 2*x + 2, mid, rx);
        }
        values[x] = merge(values[2*x + 1], values[2*x + 2]);
    }
 
    void set(int val, int pos) {
        set(val, pos, 0, 0, N);
    }
 
    int calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return NEUTRAL;
        if (l <= lx && rx <= r) return values[x];
        int mid = (lx + rx)/2;
        int s1 = calc(l, r, 2*x + 1, lx, mid);
        int s2 = calc(l, r, 2*x + 2, mid, rx);
        return merge(s1, s2);
    }
 
    int calc(int l, int r) {
        return calc(l, r, 0, 0, N);
    }
};


void solve() {
    int n, q;
    cin >> n >> q;
    segtree s;
    s.init(n);
    For (i, 0, )

}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    FASTIO;
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        solve();
    }
    return 0;
}
