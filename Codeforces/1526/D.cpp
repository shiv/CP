#include <bits/stdc++.h>
using namespace std;

#define FASTIO  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define ll long long int
#define ar array
#define ld long double
#define vll vector<ll>
#define pll pair<ll,ll>
#define vl(p) vector<p>
#define w while
#define For(i,s,x) for(i=s;i<x;i++)
#define Fore(i,s,x) for(i=s;i<=x;i++)
#define FOR(i,x) for(i=0;i<x;i++)
#define Rof(i,s,x) for(i=s;i>=x;i--)
#define all(v) v.begin(),v.end()
#define it(r,v) for(auto r=v.begin();r!=v.end();r++)
#define pb push_back
#define in insert
#define sz size()
#define F first
#define S second
#define nl cout<<"\n"
#define pr(a) cout<<a<<" "
#define pr2(a,b) cout<<a<<" "<<b<<"\n"
#define pr3(a,b,c) cout<<a<<" "<<b<<" "<<c<<"\n"

const ll mod = 1e9 + 7;
const ll N = 1e6 + 6;
const ll maxN = 30 + 15;
const ll MAX_SIZE = 2e6 + 6;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = 3.14159265359;

map<ll, ll>::iterator itr;
vector<ll>::iterator it;
set<ll>::iterator itt;
multiset<ll>::iterator itm;

bool sortbysec(const pair<int,int> &a,
              const pair<int,int> &b)
{
    return (a.second < b.second);
}

ll powerM(ll x, ll y, ll M = mod) { // default argument
    ll v = 1; x = x % M;
    while (y > 0) {if (y & 1)v = (v * x) % M; y = y >> 1; x = (x * x) % M;} return v;
}

ll power(ll x, ll y) {
    ll v = 1; while (y > 0) {if (y & 1)v = v * x; y = y >> 1; x = x * x;} return v;
}

ll fact[maxN], invfact[maxN];
ll modinv(ll a) {
    return powerM(a, mod - 2, mod);
}
ll nCr(ll n, ll r) {
    if (r > n) return 0;
    return ((fact[n] * invfact[r]) % mod * invfact[n - r]) % mod;
}
void precomputenCr() {
    fact[0] = fact[1] = 1;
    for (ll i = 2; i < maxN; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    /*
    n! = n * (n-1) !
    ==> 1/(n-1!) = n/(n!)
    ==> (1/(n-1!)) % M = (n/(n!)) % M
    ==> (1/(n-1!)) % M = ((n % M) * ((1/(n!)) % M)) % M
    */
    invfact[maxN - 1] = modinv(fact[maxN - 1]);
    for (ll i = maxN - 2; i >= 0; i--) {
        invfact[i] = invfact[i + 1] * (i + 1);
        invfact[i] %= mod;
    }
}


int largest_bit(long long x) { // based on 0-indexing
    return x == 0 ? -1 : 63 - __builtin_clzll(x);
}

void decimal(ll d)
{
std::cout << std::fixed << std::setprecision(9) <<d;
}

/*
On getting WA:
1. Check if implementation is correct and NOTHING overflows.
2. Start thinking about counter cases for your logic as well as implementation.
3. Try removing redundancy (any additon you might have done for ease of
   implementation or thought process) and putting asserts.
4. Make a generator, an unoptimized but correct soln and run it against wrong soln.


Things you may rarely use:

In C++, comparator should return false if its arguments are equal.
#define _GLIBCXX_DEBUG // Use at the top of code
cerr << "[Execution : " << (1.0 * clock()) / CLOCKS_PER_SEC << "s]\n";
int dx[] = {+1,-1,+0,+0,-1,-1,+1,+1}; // Eight Directions
int dy[] = {+0,+0,+1,-1,+1,-1,-1,+1}; // Eight Directions
int dx[]= {-2,-2,-1,1,-1,1,2,2}; // Knight moves
int dy[]= {1,-1,-2,-2,2,2,-1,1}; // Knight moves
For taking a complete line as input: string s; while(s == "") getline(cin, s);
For calculating inverse modulo, raise to the power mod-2.
For (a^b)%mod, where b is large, replace b by b%(mod-1).
x | (x + 1) sets lowest unset bit of x
x & (x - 1) unsets lowest set bit of x
x - 1 unsets the lowest set bit and sets all bits on it's right
arr.erase(unique(all(arr)), arr.end()); // erase duplicates
#define merg(a,b,c) set_union(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.begin()))
https://www.techiedelight.com/merge-two-sets-set_union-merge-cpp/
*/

int main()
{
    ll t=1;
    cin>>t;
    while(t--)
    {
      ll n,i,j;
      cin>>n;
       int v[n],p[n],sum=0;
      FOR(i,n)
      {
      cin>>v[i]>>p[i];
      ++v[i];
      sum+=v[i];
      }
      long long inf = (long long) 1e18;
       long long  t[n+1][sum+1];
      FOR(i,n+1)
      {
          FOR(j,sum+1) {
              if(i==0) t[i][j]=inf;
              if(j==0) t[i][j]=0;
          }
      }
      For(i,1,n+1) {
          For(j,1,sum+1)
          {
              if(j>=v[i-1]&&t[i-1][j-v[i-1]]!=inf)
              t[i][j]=min(t[i-1][j-v[i-1]]+p[i-1],t[i-1][j]);
              else t[i][j]=t[i-1][j];
          }
      }
      ll ans=INT_MAX;
      for(i=n;i<sum+1;i++)
      ans=min(ans,t[n][i]);
      pr(ans);
      nl;
    }
}