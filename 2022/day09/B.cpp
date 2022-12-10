#include <bits/stdc++.h>
using namespace std;

void dbg(vector<pair<int, int>>& a) {
    for(auto& [x, y]: a) cout << "(" << x << ", " << y << "), ";
    cout << "\n";
}

int main() {
    string s; 
    set<pair<int, int>> seen;
    const int m = 10;
    map<char, pair<int, int>> dir;
    dir['R'] = {0, +1};
    dir['L'] = {0, -1};
    dir['U'] = {-1, 0};
    dir['D'] = {+1, 0};
    vector<pair<int, int>> xy(m, {0, 0}), lxy(m, {0, 0});
    
    auto adj = [&](int i, int j) -> bool {
        return abs(xy[i].first - xy[j].first) <= 1 and abs(xy[i].second - xy[j].second) <= 1;
    };

    auto move = [&](int i, int dx, int dy) -> void {
        xy[i].first += dx, xy[i].second += dy;
    };

    auto pull = [&](int DX, int DY) -> void {
        xy[0].first += DX, xy[0].second += DY;
        for(int i = 1; i < m; i++) {
            int x, y, px, py;
            tie(x, y) = xy[i - 1];
            tie(px, py) = xy[i];
            if(!adj(i, i - 1)) {
                int dx = (x == px? 0: (x - px) / abs(x - px));
                int dy = (y == py? 0: (y - py) / abs(y - py));
                xy[i].first += dx, xy[i].second += dy;
            }
        }
    };

    while(getline(cin, s) and (int)s.size() > 0) {
        stringstream ss(s);
        char D; int N;
        ss >> D >> N;
        int dx, dy;
        tie(dx, dy) = dir[D];
        while(N--) {
            pull(dx, dy);
            // dbg(xy);
            seen.insert(xy[m - 1]);
        }
    } 
    
    // for(auto& [X, Y]: seen) {
        // cout << "X = " << X << ", Y = " << Y << '\n';
    // }
    cout << (int)seen.size() << '\n';

    return 0;
}
