/**
 *    author:  Shivam Gupta
 *    created: 06.03.2021 20:41:43
**/

// #undef _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;

template <typename A, typename B> string to_string(pair<A, B> p);
string to_string(const char& ch) { return "'" + string(1, ch) + "'"; }
string to_string(const string& s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string((string) s); }
string to_string(bool b) { return (b ? "true" : "false"); }
string to_string(vector<bool> v) {
    bool first = true; string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) { res += ", "; }
        first = false; res += to_string(v[i]);
    }
    res += "}"; return res;
}
template <typename A> string to_string(A v) {
    bool first = true; string res = "{";
    for (const auto &x : v) {
        if (!first) { res += ", "; }
        first = false; res += to_string(x);
    }
    res += "}"; return res;
}
template <typename A, typename B> string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
#define output cout
void debug_out() { output << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    output << " " << to_string(H);
    debug_out(T...);
}
#ifndef ONLINE_JUDGE
#define dbg(...) output << "[" << #__VA_ARGS__ << "] :", debug_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define FASTIO  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define int long long
#define vt vector
#define vii vt<int>
#define viii vt<vt<int>>
#define pii pair<int, int>
#define mii map<int, int>
#define sii set<int>
#define all(v) v.begin(), v.end()
#define sz size()
#define lb lower_bound
#define ub upper_bound
#define pb push_back
#define in insert
#define F first
#define S second
#define inf LLONG_MAX
#define For(i, n) for (int i = 0; i < n; i++)
#define Rev(i, n) for (int i = n-1; i >= 0; i--)
#define FOR(i, n) for (int i = 1; i <= n; i++)
#define REV(i, n) for (int i = n; i >= 1; i--)
#define Fore(i, a, b) for(int i = a; i <= b; i++)
#define memset(x, y) memset(x, y, sizeof(x))
#define fps(x, y) fixed << setprecision(y) << x
#define caseno(i) cout << "Case #" <<i << ": "
#define Time() cerr << "[Execution : " << (1.0 * clock())/CLOCKS_PER_SEC << "s]\n"

template <typename T, typename U>
istream& operator>>(istream& in, pair<T,U>& a) { in >> a.F >> a.S; return in; }
template <typename T, typename U>
ostream& operator<<(ostream& out,pair<T,U>& a) { out << a.F << " " << a.S; return out; }
template <typename T>
istream& operator>>(istream& in, vt<T>& a) { for (T& x : a) in >> x; return in; }
template <typename T>
ostream& operator<<(ostream& out, vt<T>& a) {
    bool f = false;
    for (T& x : a) { if (f) out << " "; out << x; f = true; } out << '\n';
    return out;
}
void out(bool ok, bool cap = true) {
    if (cap) cout << (ok ? "YES" : "NO") << '\n';
    else cout << (ok ? "Yes" : "No") << '\n';
}

void pr() {}
template <typename Head, typename... Tail>
void pr(Head H, Tail... T) { cout << H << " "; pr(T...); }
void print() { cout << '\n'; }
template <typename Head>
void print(Head H) { cout << H; print(); }
template <typename Head, typename... Tail>
void print(Head H, Tail... T) { cout << H << " "; print(T...); }

template <typename T, typename U>
T amax(T& a, U b) { if (b > a) a = b; return a; }
template <typename T, typename U>
T amin(T& a, U b) { if (b < a) a = b; return a; }
int rand_int(int l, int r) {
  static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
  return uniform_int_distribution<int>(l, r)(gen);
}
template<typename T>
void myshuffle(vt<T> &a){
  for (int i = 0; i < a.size(); i++) swap(a[i], a[rand_int(0, i)]);
}

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

const int mod = 1000000007;

const int M = 2e5;
int P[M+1];
vii primes(int n) {  vii p; for (int j, i = 2; i <= n; i++) if (!P[i]) for (p.pb(i), j = i * i; j <= n; j += i) P[j]++; return p; }
int largest_bit(int x) { return x==0 ? -1 : 63 - __builtin_clzll(x); }
int gcd(int a, int b) { if(a < b) return gcd(b, a);if (!b) return a; return gcd(b, a % b); }
int lcm(int a, int b) { return a / gcd(a, b) * b; }
int add(int a, int b) { a %= mod; b %= mod; a = (a + b) % mod; return a; }
int mul(int a, int b) { a %= mod; b %= mod; a = (a * b) % mod; return a; }
int sub(int a, int b) { a %= mod; b %= mod; a = ((a - b) % mod + mod) % mod; return a; }
int exp(int x, int y, int m = mod) { int res = 1; x = x % m; while (y > 0) { if (y & 1) res = (res * x) % m; y = y >> 1; x = (x * x) % m; } return res; }
int modinv(int x, int m = mod) { return exp(x, m - 2, m); }
viii readGraph(int n, int m) { viii g(n); int a, b;
    for (int i = 0; i < m; i++) { cin >> a >> b; a--; b--; g[a].pb(b); g[b].pb(a); }
    return g;
}

const int N = 3e5+5;

void preSolve(int *t) {
}

void solve() {
    int n, q;
    cin >> n >> q;
    vii a(n);
    cin >> a;

    int GCD = a[0];
    for (int i = 1; i < n; i++)
        GCD = gcd(GCD, a[i]);
    for (int i = 0; i < n; i++)
        a[i] /= GCD;

    map<int, int> m[n];
	vii allPrime = primes(M);
    vii prime = primes(sqrt(M));
    int prime_size = prime.size();
    for (int j = 0, i = 2; i <= M; i++) {
        if (P[i] == 0)
            P[i] = j++;
        else
            P[i] = -1;
    }

    set<int> S[allPrime.sz];

    auto check = [&] (int index, int p) {
        if (S[index].sz == n) {
            S[index].clear();
            int mini = inf;
            for (int i = 0; i < n; i++)
                amin(mini, m[i][p]);
            for (int i = 0; i < n; i++) {
                m[i][p] -= mini;
                if (m[i][p])
                    S[index].in(i);
            }
            while (mini--)
                GCD = mul(GCD, p);
        }
    };

    auto update = [&] (int i, int curr, bool ok) {
        for (int j = 0; j < prime_size; j++) {
            int p = prime[j];
            if (curr % p == 0) {
                while (curr % p == 0) {
                    curr /= p;
                    m[i][p]++;
                }
                S[j].in(i);
                if (ok)
                    check(j, p);
            }
            if (curr == 1)
                break;
        }
        if (curr != 1) {
            m[i][curr]++;
            int index = P[curr];
            S[index].in(i);
            if (ok)
                check(index, curr);
        }
    };

    for (int i = 0; i < n; i++) {
        update(i, a[i], false);
    }

	while (q--) {
		int i, x;
		cin >> i >> x;
        update(i - 1, x, true);
        print(GCD);
	}
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    FASTIO;
    int t = 1;
    preSolve(&t);
    for (int i = 1; i <= t; i++) {
        solve();
    }
    return 0;
}
