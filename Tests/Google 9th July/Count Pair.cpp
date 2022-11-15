#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree< int ,  null_type ,  less_equal<int> ,  rb_tree_tag ,  tree_order_statistics_node_update >

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n, c, d;
        cin >> n >> c >> d;
        vector<int> a(n), b(n), f(n);
        for(int i = 0; i < n; i++)
            cin >> a[i];
        for(int i = 0; i < n; i++)
            cin >> b[i];

        for(int i = 0; i < n; i++)
            f[i] = a[i]-b[i];
        ordered_set cnt; // MULTISET PBDS
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += cnt.order_of_key(f[i] + d-c+1);
            cnt.insert(f[i]);
        }
        cout << ans << '\n';
    }
    return 0;
}