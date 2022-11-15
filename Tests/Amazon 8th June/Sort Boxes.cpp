#include "bits/stdc++.h"
#include <algorithm>
using namespace std;

vector<string> sortBoxes(vector<string> boxList) {

    vector<string> ans;

    vector<string> older, newer;
    vector<pair<string, string>> older_, newer_;
    for (string &s : boxList) {
        auto space = s.find(' ');
        if ('0' <= s[space + 1] && s[space + 1] <= '9') {
            newer.push_back(s);
            newer_.emplace_back(s.substr(0, space), s.substr(space + 1, s.size()));
        }
        else {
            older.push_back(s);
            older_.emplace_back(s.substr(0, space), s.substr(space + 1, s.size()));
        }
    }

    {
        vector<int> idx(older.size());
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&] (int i, int j) {
            if (older_[i].second == older_[j].second) {
                return older_[i].first < older_[j].first;
            }
            return older_[i].second < older_[j].second;
        });

        for (int &i : idx) {
            ans.push_back(older[i]);
        }
    }

    {
        for (auto &s : newer) {
            ans.push_back(s);
        }
    }


    return ans;
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        sortBoxes({{"ykc 82 01"}, {"eo first qpx"}, {"09z cat hamster"}, {"06f 12 25 6"}, {"az0 first qpx"}, {"236 cat dog rabbit snake"}});
    }

    return 0;
}


/*
    My approach:
        Firstly I sperated the older generation boxes from the newer generation boxes by checking whether the first character of the second word of the string is a number or not.
        Then I sorted the older generation boxes by the rules:
            - On the basis the string after the first word of the string
            - If the above rules does not apply, sort by the first word of the string
        Then I added the sorted older generation boxes to the answer vector.
        Finally I added the unsorted newer generation boxes separated earlier to the answer vector.
    Run-time Complexity: O(n * log(n) * m)
        where n is the number of boxes
        and m is the maximum length of each string
*/