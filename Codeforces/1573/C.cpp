#include "bits/stdc++.h"
#include <algorithm>
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

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;
// Class to represent a graph
class Graph {
    int V; // No. of vertices'

    // Pointer to an array containing
    // adjacency listsList
    list<int>* adj;

public:
    Graph(int V); // Constructor

    // Function to add an edge to graph
    void addEdge(int u, int v);

    // Function to print the required topological
    // sort of the given graph
    vector<int> topologicalSort();
};

// Constructor
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

// Function to add an edge to the graph
void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}

// Function to print the required topological
// sort of the given graph
vector<int> Graph::topologicalSort()
{
    // Create a vector to store indegrees of all
    // the vertices
    // Initialize all indegrees to 0
    vector<int> in_degree(V, 0);

    // Traverse adjacency lists to fill indegrees of
    // vertices
    // This step takes O(V+E) time
    for (int u = 0; u < V; u++) {
        list<int>::iterator itr;
        for (itr = adj[u].begin(); itr != adj[u].end(); itr++)
            in_degree[*itr]++;
    }

    // Create a set and inserting all vertices with
    // indegree 0
    multiset<int> s;
    for (int i = 0; i < V; i++)
        if (in_degree[i] == 0)
            s.insert(i);

    // Initialize count of visited vertices
    int cnt = 0;

    // Create a vector to store result (A topological
    // ordering of the vertices)
    vector<int> top_order;

    // One by one erase vertices from setand insert
    // adjacents if indegree of adjacent becomes 0
    while (!s.empty()) {

        // Extract vertex with minimum number from multiset
        // and add it to topological order
        int u = *s.begin();
        s.erase(s.begin());
        top_order.push_back(u);

        // Iterate through all its neighbouring nodes
        // of erased node u and decrease their in-degree
        // by 1
        list<int>::iterator itr;
        for (itr = adj[u].begin(); itr != adj[u].end(); itr++)

            // If in-degree becomes zero, add it to queue
            if (--in_degree[*itr] == 0)
                s.insert(*itr);

        cnt++;
    }

    // Check if there was a cycle
    if (cnt != V) {
        // cout << -1;
        return vector<int>(0);
    }

    // Print topological order
    return top_order;
    // for (int i = 0; i < top_order.size(); i++)
    //     cout << top_order[i] << " ";
}

void solve() {

    int n;
    scan(n);

    Graph g(n);

    for (int i = 0; i < n; i++) {
        int k;
        scan(k);
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            g.addEdge(a - 1, i);
        }
    }

    auto topo = g.topologicalSort();
    if (topo.empty()) {
        print(-1);
    }
    else {
        int ans = 0;
        // set<int> s;
        // for (int &i : topo) {
        //     i = -i;
        //     auto low = s.lower_bound(i);
        //     if (low == s.end()) {
        //         s.insert(i);
        //     }
        //     else {
        //         int temp = *low;
        //         s.erase(low);
        //         s.insert(i);
        //     }
        // }
        dbg(topo);
        // print(s.size());
        // fo
        print(ans);
    }
}

signed main() {

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