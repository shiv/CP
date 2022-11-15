#include "bits/stdc++.h"
using namespace std;

class Trie {
public:

    struct node {
        vector<node*> child;
        int no;

        node () {
            no = 0;
            child = vector<node*>(26, NULL);
        }
    };

    node *root;

    Trie () {
        root = new node();
    }

    node* add (string &s, int idx = 0, node *cur = NULL) {
        if (cur == NULL) cur = root;

        for (int i = idx; i < s.size(); i++) {
            int ch = s[i] - 'a';

            if (!cur->child[ch])
                cur->child[ch] = new node();

            cur = cur->child[ch];
            cur->no += 1;
        }
        return cur;
    }

    int cal (string &s) {
        int ans = 0;
        auto curr = root;
        for (int i = 0; i < s.size(); i++) {
            ans += curr->child[s[i] - 'a']->no;
            curr = curr->child[s[i] - 'a'];
        }
        return ans;
    }

};

void solve() {

    int n, k;
    cin >> n >> k;

    Trie trie;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        trie.add(s[i]);
    }

    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
        ans[i] = trie.cal(s[i]);
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}