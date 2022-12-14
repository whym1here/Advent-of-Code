#include <bits/stdc++.h>
using namespace std;

const int mxn = 550, mxm = 200;

vector<string> readlines() {
    string s;
    vector<string> S;
    while(getline(cin, s) and (int)s.size() > 0) S.push_back(s);
    return S;
}

vector<string> split(string s) {
    vector<string> S;
    stringstream ss(s);
    while(ss >> s) S.push_back(s);
    return S;
}

void replace(string& S, char cur, char nxt) {
    const int n = (int)S.size();
    for(int i = 0; i < n; i++) {
        if(S[i] == cur) S[i] = nxt;
    }
}

void dis(vector<vector<int>>& sim) {
    const int n = (int)sim.size(), m = (int)sim[0].size();
    for(int j = 0; j < m; j++) {
        for(int i = 0; i < n; i++) {
            cout << (sim[i][j] == 0? '.': '#');
        } 
        cout << '\n';
    }
    cout << '\n';
}


int main() {
    auto lines = readlines();
    vector<vector<pair<int, int>>> a;
    int mxn = 0, mxm = 0;
    for(auto& line: lines) {
        replace(line, ',', ' ');
        replace(line, '-', ' ');
        replace(line, '>', ' ');
        stringstream ss(line);
        int x, y; 
        vector<pair<int, int>> b;
        while(ss >> x >> y) {
            b.push_back({x, y});
            // cout << "x = " << x << ", y = " << y << '\n';
            mxn = max(x, mxn);
            mxm = max(y, mxm);
        }
        a.push_back(b);
    }

    mxn = mxm = max(mxm + 100, mxn + 100);
    vector<vector<int>> sim(mxn, vector<int>(mxm, 0));
    // 0 == empty, 1 = sand

    auto fill_sand = [&](int x1, int y1, int x2, int y2) -> void {
        int dx = (x1 > x2? -1: +1), dy = (y1 > y2? -1: +1);
        for(int i = x1; (dx > 0? i <= x2: i >= x2); i += dx) {
            for(int j = y1; (dy > 0? j <= y2: j >= y2); j += dy) {
                sim[i][j] = 1;
            } 
        }
    };

    for(auto& line: a) {
        for(int i = 1; i < (int)line.size(); i++) {
            int x1, y1, x2, y2;
            tie(x1, y1) = line[i - 1];
            tie(x2, y2) = line[i];
            fill_sand(x1, y1, x2, y2);
        }
    }
    // dis(sim);
    bool stop = true;

    auto ok = [&](int x, int y) -> bool {
        return 0 <= x and x < mxn and 0 <= y and y < mxm;
    };
    int sand = 0;
    function<void(int, int)> dfs = [&](int x, int y) -> void {
        if(y == mxm - 1) {
            stop = false;
            sand--;
        }
        sim[x][y] = 1;
        bool done = false;
        if(!done and ok(x, y + 1) and sim[x][y + 1] == 0) {
            sim[x][y] = 0;
            dfs(x, y + 1);
            done = true;
        }
        if(!done and ok(x - 1, y + 1) and sim[x - 1][y + 1] == 0) {
            sim[x][y] = 0;
            dfs(x - 1, y + 1);
            done = true;
        }
        if(!done and ok(x + 1, y + 1) and sim[x + 1][y + 1] == 0) {
            sim[x][y] = 0;
            dfs(x + 1, y + 1);
            done = true;
        }
        sand += !done;
    };

    int ox = 500, oy = 0;
    while(stop) {
        dfs(ox, oy);
        // dis(sim);
    }
    cout << sand << '\n';

    return 0;
}
