#include "bits/stdc++.h"
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second; }
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "["; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "]"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void scan() {} template <typename Head, typename ...Tail> void scan(Head &H, Tail &...T) { cin >> H; scan(T...); }
void print() { cout << "\n"; } template <typename Head> void print(const Head &H) { cout << H << "\n"; } template <typename Head, typename ...Tail> void print(const Head &H, const Tail &...T) { cout << H << " "; print(T...); }
template <typename Head> void dbg_out(string var, const Head &H) { cerr << var << " = " << H << endl; } template <typename Head, typename ...Tail> void dbg_out(string var, const Head &H, const Tail &...T) { for (int i = 0, b = 0; i < (int)var.size(); i++) { if (var[i] == '(' || var[i] == '{') b++; else if (var[i] == ')' || var[i] == '}') b--; else if (var[i] == ',' && b == 0) { cerr << var.substr(0, i) << " = " << H << " | "; dbg_out(var.substr(var.find_first_not_of(' ', i + 1)), T...); break; } } }
#ifndef ONLINE_JUDGE
#define dbg(...) debug = true, dbg_out(#__VA_ARGS__, __VA_ARGS__), debug = false
#else
#define dbg(...)
#endif

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;
int row[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
int col[] = { -1, 1, 1, -1, 2, -2, 2, -2 };

// Check if (x, y) is valid chessboard coordinates.
// Note that a knight cannot go out of the chessboard
bool isValid(int x, int y, int N) {
    return (x >= 0 && x < N) && (y >= 0 && y < N);
}

// A queue node used in BFS
struct Node
{
    // (x, y) represents chessboard coordinates
    // `dist` represents its minimum distance from the source
    int x, y, dist;

    // Node constructor
    Node(int x, int y, int dist = 0): x(x), y(y), dist(dist) {}

    // As we are using struct as a key in a `std::set`,
    // we need to overload `<` operator`.
    // Alternatively, we can use `std::pair<int, int>` as a key
    // to store the matrix coordinates in the set.

    bool operator<(const Node& o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
};

// Find the minimum number of steps taken by the knight
// from the source to reach the destination using BFS
int findShortestDistance(int N, Node src, Node dest)
{
    // set to check if the matrix cell is visited before or not
    set<Node> visited;

    // create a queue and enqueue the first node
    queue<Node> q;
    q.push(src);

    // loop till queue is empty
    while (!q.empty())
    {
        // dequeue front node and process it
        Node node = q.front();
        q.pop();

        int x = node.x;
        int y = node.y;
        int dist = node.dist;

        // if the destination is reached, return distance
        if (x == dest.x && y == dest.y) {
            return dist;
        }

        // skip if the location is visited before
        if (!visited.count(node))
        {
            // mark the current node as visited
            visited.insert(node);

            // check for all eight possible movements for a knight
            // and enqueue each valid movement
            for (int i = 0; i < 8; i++)
            {
                // get the knight's valid position from the current position on
                // the chessboard and enqueue it with +1 distance
                int x1 = x + row[i];
                int y1 = y + col[i];

                if (isValid(x1, y1, N)) {
                    q.push({x1, y1, dist + 1});
                }
            }
        }
    }

    // return infinity if the path is not possible
    return INT_MAX;
}

void solve() {

    int x, y;
    scan(x, y);

    int ans = 0;
    {
        int curr = min(x / 4, y / 4);
        x -= curr * 4;
        y -= curr * 4;
        ans += curr * 2;
    }
    {
        int curr = min(x / 2, y / 4);
        curr = max<int>(0, curr - 1);
        x -= curr * 2;
        y -= curr * 4;
        ans += curr * 2;
    }
    {
        int curr = min(x / 4, y / 2);
        curr = max<int>(0, curr - 1);
        x -= curr * 4;
        y -= curr * 2;
        ans += curr * 2;
    }
    {
        int curr = x / 4;
        curr = max<int>(0, curr - 1);
        x -= curr * 4;
        ans += curr * 2;
    }
    {
        int curr = y / 4;
        curr = max<int>(0, curr - 1);
        y -= curr * 4;
        ans += curr * 2;
    }
    ans += findShortestDistance(N, {0, 0}, {x, y});
    print(ans);
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