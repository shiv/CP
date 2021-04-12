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
#define Fore(i, a, b)    for (int i = a; i <= b; i++)

const int mod = 1000000007;

void presolve(int &t) {
    cin >> t;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    viii a(n + 1, vii(m + 1));
    Fore(i, 1, n)
    	Fore(j, 1, m)
    		cin >> a[i][j];

    viii b = a;
    Fore (i, 1, n)
    	Fore(j, 1, m)
    		b[i][j] += b[i][j - 1];

    Fore (i, 1, n)
    	Fore(j, 1, m)
    		b[i][j] += b[i - 1][j];

    auto cal = [&] (int i, int j, int o) {
    	int sum = b[i][j] - b[i - o][j] - b[i][j - o] + b[i - o][j - o];
    	return sum >= k * o * o;
    };

    auto check = [&] (int o) {
    	int sum = 0;
    	Fore (i, o, n) {
    		int low = o, high = m;
    		if (cal(i, low, o))
    			sum += m - low + 1;
    		else if (cal(i, high, o)) {
    			low++;
    			while (low <= high) {
    				int mid = (low + high) / 2;
    				if (cal(i, mid, o)) {
    					if (!cal(i, mid - 1, o)) {
    						sum += m - mid + 1;
    						break;
    					}
    					high = mid - 1;
    				}
    				else
    					low = mid + 1;
    			}
    		}
    	}
    	return sum;
    };

    int ans = 0;
    Fore (i, 1, n)
    	ans += check(i);

   	cout << ans << '\n';
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