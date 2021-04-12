/**
 *    author:  Shivam Gupta
 *    created: 11.04.2021 20:55:03
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
#define For(i, a, b)    for (int i = a; i < b; i++)
#define Rev(i, a, b)    for (int i = b - 1; i >= a; i--)
#define Fore(i, a, b)   for (int i = a; i <= b; i++)
#define Reve(i, a, b)    for (int i = b; i >= a; i--)
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

const int N = 2e5+5;
class Edge {
public:
    int src, dest, weight;
};
 
// a structure to represent a connected,
// undirected and weighted graph
class Graph {
public:
     
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges.
    // Since the graph is undirected, the edge
    // from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
    Edge* edge;
};
 
// Creates a graph with V vertices and E edges
Graph* createGraph(int V, int E)
{
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
 
    graph->edge = new Edge[E];
 
    return graph;
}
 
// A structure to represent a subset for union-find
class subset {
public:
    int parent;
    int rank;
};
 
// A utility function to find set of an element i
// (uses path compression technique)
int find(subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent
            = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
// A function that does union of two sets of x and y
// (uses union by rank)
void Union(subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    // If ranks are same, then make one as root and
    // increment its rank by one
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 
// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int32_t myComp(const void* a, const void* b)
{
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}
 
// The main function to construct MST using Kruskal's
// algorithm
int KruskalMST(Graph* graph)
{
    int V = graph->V;
    Edge result[V]; // Tnis will store the resultant MST
    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges
 
    // Step 1: Sort all the edges in non-decreasing
    // order of their weight. If we are not allowed to
    // change the given graph, we can create a copy of
    // array of edges
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]),
          myComp);
 
    // Allocate memory for creating V ssubsets
    subset* subsets = new subset[(V * sizeof(subset))];
 
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < graph->E)
    {
        // Step 2: Pick the smallest edge. And increment
        // the index for next iteration
        Edge next_edge = graph->edge[i++];
 
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
 
        // If including this edge does't cause cycle,
        // include it in result and increment the index
        // of result for next edge
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }
 
    // print the contents of result[] to display the
    // built MST
    int minimumCost = 0;
    for (i = 0; i < e; ++i)
    {
        minimumCost = minimumCost + result[i].weight;
    }
    return minimumCost;
}

void preSolve(int &t) {
    cin >> t;
}

void solve() {
    int n, p;
    cin >> n >> p;
    vii a(n);
    cin >> a;
    

    // int e = 2;
    // Graph* graph = createGraph(n, e);

    // for (int i = 0; i < e - 1; i++) {
	   //  graph->edge[i].src = i;
	   //  graph->edge[i].dest = i + 1;
	   //  graph->edge[i].weight = p;
    // }

 
    // int ans = KruskalMST(graph);
    // print(ans);

    auto isPeak = [&] (int i) {
    	if (i > 0 && a[i - 1] < a[i])
	        return false;
	  
	    // If num is smaller than the element
	    // on the right (if exists)
	    if (j < n && arr[j] > num)
	        return false;
	    return true;
    };

    int i, j;
    i = 1; j = 0;
    while (i < n) {
    	
    }

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
