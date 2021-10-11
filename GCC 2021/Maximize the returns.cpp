#include <bits/stdc++.h>
using namespace std;

template<typename input>
class segtree {
public:

    class node {
    public:

        int val, lazy;

        friend istream& operator>>(istream &in, node &n) {
            return in >> n.val;
        }
        friend ostream& operator<<(ostream &out, const node &n) {
            return out << n.val;
        }

        // set initial values
        node(int _val = 0, int _lazy = 0) : val(_val), lazy(_lazy) {}

        // merging of two nodes
        friend node merge(node &a, node &b) {
            node c;
            c.val = max(a.val, b.val);
            return c;
        }

        // lazy operation
        void apply(int lx, int rx, const node &other) {
            val += other.lazy;
            lazy += other.lazy;
        }
    };

    // neutral element
    node identity_element = -(int)1e18;

    // conversion of input to node
    node make_node(input val, input lazy) {
        node m = node(val, lazy);
        return m;
    }

    int size;
    vector<node> nodes;

    inline void push(int x, int lx, int rx) {
        if (nodes[x].lazy != identity_element.lazy) {
            int m = (lx + rx) >> 1;
            nodes[x << 1 | 0].apply(lx, m, nodes[x]);
            nodes[x << 1 | 1].apply(m, rx, nodes[x]);
            nodes[x].lazy = identity_element.lazy;
        }
    }

    inline void pull(int x, int lx, int rx) {
        nodes[x] = merge(nodes[x << 1 | 0], nodes[x << 1 | 1]);
    }

    segtree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        nodes.resize(2 * size);
    }

    segtree(vector<input> &a) {
        int n = a.size();
        size = 1;
        while (size < n) size <<= 1;
        nodes.resize(2 * size);
        build(a);
    }

    void build(vector<input> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size())
                nodes[x] = make_node(a[lx], node().lazy);
            return;
        }
        push(x, lx, rx);
        int m = (lx + rx) >> 1;
        build(a, x << 1 | 0, lx, m);
        build(a, x << 1 | 1, m, rx);
        pull(x, lx, rx);
    }

    void build(vector<input> &a) {
        build(a, 1, 0, size);
    }

    void update(int l, int r, input v, int x, int lx, int rx) {
        if (lx >= r || l >= rx)
            return;
        if (lx >= l && rx <= r) {
            nodes[x].apply(lx, rx, make_node(node().val, v));
            return;
        }
        push(x, lx, rx);
        int m = (lx + rx) >> 1;
        update(l, r, v, x << 1 | 0, lx, m);
        update(l, r, v, x << 1 | 1, m, rx);
        pull(x, lx, rx);
    }

    void update(int l, int r, input v) {
        update(l, r + 1, v, 1, 0, size);
    }

    void update(int i, input v) {
        update(i, i, v);
    }

    node query(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx)
            return identity_element;
        if (lx >= l && rx <= r)
            return nodes[x];
        push(x, lx, rx);
        int m = (lx + rx) >> 1;
        node q1 = query(l, r, x << 1 | 0, lx, m);
        node q2 = query(l, r, x << 1 | 1, m, rx);
        pull(x, lx, rx);
        return merge(q1, q2);
    }

    node query(int l, int r) {
        return query(l, r + 1, 1, 0, size);
    }

    node query(int i) {
        return query(i, i);
    }
};

int calculateMaximizedReturns(int n, int k, int d, int m, vector<int> returns) {

    vector<vector<int>> invest(k + 1, vector<int>(n + 1, (int)-1e18));
    invest[0] = vector<int>(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        invest[0][i] = returns[i] + (i == n - 1 ? 0  : invest[0][i + 1]);
    }

    for (int idx = 0; idx < k; idx++) {

        segtree<int> seg(n);

        for (int ret = n - 1; ret >= 0; ret--) {

            seg.update(ret, ret, invest[idx][ret + 1]);

            int temp = min(n - 1, ret + d);
            if (ret <= temp) {
                invest[idx + 1][ret] = seg.query(ret, temp).val;
            }
            invest[idx + 1][ret] = max(invest[idx + 1][ret], returns[ret] + invest[idx + 1][ret + 1]);
            seg.update(ret, n - 1, m * returns[ret]);
        }
    }

    int mx = 0;
    for (int &i : invest[k]) {
        mx = max(mx, i);
    }

    return mx;
}

vector<string> split(const string& str, char delim) {
    vector<string> strings;
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != string::npos) {
        end = str.find(delim, start);
        strings.push_back(str.substr(start, end - start));
    }
    return strings;
}

vector<int> splitStringToInt(const string& str, char delim) {
    vector<int> strings;
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != string::npos) {
        end = str.find(delim, start);
        strings.push_back(stoi(str.substr(start, end - start)));
    }
    return strings;
}

void printVector(vector<int> vec) {
    for (vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i) {
        cout << *i << ' ';
    }
    cout << endl;
}

void printVector(vector<string> vec) {
    for (vector<string>::const_iterator i = vec.begin(); i != vec.end(); ++i) {
        cout << *i << ' ';
    }
    cout << endl;
}

signed main() {
    string firstLine;
    getline(cin, firstLine);

    vector<int> firstLineVec = splitStringToInt(firstLine, ' ');
    int n = firstLineVec[0];
    int k = firstLineVec[1];
    int d = firstLineVec[2];
    int m = firstLineVec[3];

    string returns;
    getline(cin, returns);

    vector<int> returnsVec = splitStringToInt(returns, ' ');

    int result = calculateMaximizedReturns(n, k, d, m, returnsVec);

    // Do not remove below line
    cout << result << "\n";
    // Do not print anything after this line

    return 0;
}

