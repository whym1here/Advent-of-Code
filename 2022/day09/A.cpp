#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; 
    set<pair<int, int>> seen;
    int x = 0, y = 0;
    int px = 0, py = 0;
    
    map<char, pair<int, int>> dir;
    dir['R'] = {0, +1};
    dir['L'] = {0, -1};
    dir['U'] = {-1, 0};
    dir['D'] = {+1, 0};

    vector<pair<int, int>> dxdy = {
        {-1, -1}, {+1, +1}, {-1, +1}, {+1, -1},
        {0, -1}, {0, +1}, {-1, 0}, {+1, 0}, 
        {0, 0}
    };
    while(getline(cin, s) and (int)s.size() > 0) {
        stringstream ss(s);
        char D; int N;
        ss >> D >> N;
        //cout << "N = " << N << ", ";
        int dx, dy;
        tie(dx, dy) = dir[D];
        //cout << "D = " << D << ", dx = " << dx << ", dy = " << dy << '\n';
        int lx = x, ly = y;
        while(N--) {
            bool ok = true; 
            x += dx, y += dy;
            for(auto& [nx, ny]: dxdy) {
                if(px + nx == x and py + ny == y) {
                    ok = false;
                }
            }
            if(ok) px = lx, py = ly;
            lx = x, ly = y;
            seen.insert({px, py});
        }
    } 
    for(auto& [X, Y]: seen) {
        cout << "X = " << X << ", Y = " << Y << '\n';
    }
    cout << (int)seen.size() << '\n';

    return 0;
}
