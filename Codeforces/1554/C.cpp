#include <bits/stdc++.h>
using namespace std;

#define ll int64_t

/*
HealthyUG
https://youtu.be/2jS7BxsbsAk?t=982
SecondThread
https://youtu.be/SU1nUL6SI0Q?t=6991
Errichto
https://youtu.be/Gv5kdcw-WrU?t=813
Geothermal
https://youtu.be/zfz9m2M8A1M?t=6834


If mex = x, this means all numbers from 0 to x-1 are present.
=> n^{sth} = {0..x-1}
=> {sth} = {0..x-1}^n
=> 0 <= {sth} <= m

Which means that n ^ sth_x = x
=> sth_x = x ^ n
=> sth_x > m

There can be many x such that x ^ n > m
but since we are talking about max, we want
minimum x
*/

void preSolve(int& testcases) {
    cin >> testcases;
}

void solve() {
    int n, m;
    cin >> n >> m;
    // we can always find a mask whose xor (can also be seen as or
    // since we are not setting any common bit in x and n) with n will give
    // value which will be >= m+1
    ++m;
    int x = 0;
    for (int i = 31; i >= 0 && n < m; --i) {
        if ((m & (1 << i) && (n & (1 << i)) == 0)) {
            // bit is set is m but not in n
            n |= (1 << i);
            x |= (1 << i);
            if (n > m)  {
                break;
            }
        }
    }
    cout << x << '\n';
}

/*
int n, m;
cin >> n >> m;
int x = 0, tn = n;
if (n <= m) {
    for (int i = 31; i >= 0; --i) {
        if (m & (1 << i)) {
            if ((n & (1 << i)) == 0) {
                // bit is set is m but not in n
                n |= (1 << i);
                x |= (1 << i);
                if (n > m)  {
                    break;
                }
            }
        }
    }
}
if (n == m) {
    // now we have to set the smallest unset bit and
    // unset all the smallest bits which weren't there
    // in n but got set as it were in m

    int b = (n | (n + 1)) - n; // lowest unset bit value
    x = x + b; // equivalent to setting the lowest unsent bit value
    n = n | (n + 1); // setting the lowest set bit value
    assert(n > m);
    for (int i = 0; i <= 31; i++) {
        if ((m & (1 << i)) && ((tn & (1 << i)) == 0)) {
            if ((n ^ (1 << i)) > m) {
                n = n ^ (1 << i);
                x = x ^ (1 << i);
            }
        }
    }
}
cout << x << '\n';
*/

signed main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int testcases = 1;
    preSolve(testcases);
    for (int caseno = 1; caseno <= testcases; ++caseno) {
        solve();
    }
    return 0;
}
