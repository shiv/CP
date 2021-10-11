#include <bits/stdc++.h>

using namespace std;

void normalise (int &x, int &y) {
    int gcd = __gcd(x, y);
    x /= gcd;
    y /= gcd;
}

struct line {
    int mx, my, c;

    line () {}

    line (int x1, int y1, int x2, int y2) {
        int delta_x = x1 - x2;
        int delta_y = y1 - y2;
        normalise(delta_x, delta_y);
        mx = delta_x;
        my = delta_y;
        c = y1 * delta_x - x1 * delta_y;
    }

    friend ostream& operator<<(ostream &os, const line &n) {
        return os << n.mx << ' ' << n.my << ' ' << n.c;
    }
};

bool operator<(const line a, const line &other) {
        if (a.mx != other.mx) {
        return a.mx < other.mx;
    }
    if (a.my != other.my) {
        return a.my < other.my;
    }
    return a.c < other.c;
}

int main() {

    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        x[i] += 1000;
        y[i] += 1000;
    }
    int ans = 0;

    map<line, set<pair<int, int>>> pt;
    set<pair<int, line>> set_;

    auto calc = [&] () {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                line line_param(x[i], y[i], x[j], y[j]);
                pt[line_param].emplace(x[i], y[i]);
                pt[line_param].emplace(x[j], y[j]);
            }
        }
    };
    calc();

    auto Erase = [&] (line &l, int x, int y) {
        auto it = pt[l].find({x, y});
        if(it != pt[l].end()) {
            pt[l].erase(it);
        }
    };

    for(auto it = pt.begin(); it != pt.end(); it++) {
        int sz = it->second.size();
        set_.insert({sz, it->first});
    }

    while(!set_.empty()) {
        auto it = prev(set_.end());
        int sz = it->first;
        auto line_param1 = it->second;
        if(sz == 0) {
            break;
        }
        set_.erase(it);
        ans++;
        auto& vec = pt[line_param1];
        for(auto& P : vec) {
            int x_ = P.first, y_ = P.second;
            for(int i = 0; i < n; i++) {
                int delta_x = x[i] - x_;
                int delta_y = y[i] - y_;
                if (delta_x == 0 && delta_y == 0) {
                    continue;
                }
                normalise(delta_x, delta_y);
                line line_param(x[i], y[i], x_, y_);
                if ((line_param.mx == line_param1.mx) && (line_param.my == line_param1.my) && (line_param.c == line_param1.c)) {
                    continue;
                }
                set_.erase({pt[line_param].size(), line_param});
                Erase(line_param, x[i], y[i]);
                Erase(line_param, x_, y_);
            }
        }
    }
    cout << ans;
    return 0;
}