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

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

int func( int src,int par,int curdist,vector<vector<int>>& graph,vector<int>&dist,vector<int>&nodes)
{
    dist[src] = curdist;

    if( src != 0 && graph[src].size() == 1 ) nodes[src] = 0;
    else
    {
        for( int i = 0; i < graph[src].size() ; i++ )
        {
            if( graph[src][i] == par ) continue;
            nodes[src] += func(graph[src][i],src,curdist+1,graph,dist,nodes);
        }
    }

    nodes[src]++;

    return nodes[src];
}

vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {

    vector<vector<int>>graph(n);

    for( int i = 0; i < n-1; i++ )
    {
        graph[edges[i][0] - 1].push_back(edges[i][1] - 1);
        graph[edges[i][1] - 1].push_back(edges[i][0] - 1);
    }

    vector<int>dist(n,0),ans(n,0),nodes(n,0);

    func(0,-1,0,graph,dist,nodes);

    for( int i = 0; i < n; i++ )
    {
        ans[0] += dist[i];
    }

    queue<int>myqueue;
    myqueue.push(0);

    while( myqueue.size() != 0 )
    {
        int node1 = myqueue.front();
        myqueue.pop();

        for( int i = 0; i < graph[node1].size(); i++ )
        {
            int node2 = graph[node1][i];

            if( ans[node2] == 0 )
            {
                ans[node2] = ans[node1] + n - 2*nodes[node2];
                myqueue.push(node2);
            }
        }

    }

    return ans;

}

void solve() {

    int n;
    scan(n);
    vector<vector<int>> edges(n - 1, vector<int>(2));
    scan(edges);

    for (int &i : sumOfDistancesInTree(n, edges)) {
        print(i);
    }
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}