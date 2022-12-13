#include<bits/stdc++.h>
using namespace std;

vector<string> readlines() {
    vector<string> S;
    string s;
    while(getline(cin, s) and s.size() > 0) S.push_back(s);
    return S;
}

int main() {
    auto S = readlines();
    const int n = (int)S.size(), m = (int)S[0].size();
    
    array<int, 2> st, ed;
    queue<array<int, 2>> q; 
    vector<vector<int>> d(n, vector<int>(m, -1));
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(S[i][j] == 'S') {
                st = {i, j};
                S[i][j] = 'a';
                d[i][j] = 0;
                q.push({i, j});
                cout << "i = " << i << ", j = " << j << '\n';
            } else if(S[i][j] == 'E') { 
                ed = {i, j};
                S[i][j] = 'z';
            } else if(S[i][j] == 'a') {
                d[i][j] = 0;
                cout << "i = " << i << ", j = " << j << '\n';
                q.push({i, j});
            }
        }
    }
    
    auto ok = [&](int x, int y) -> bool {
        return 0 <= x and x < n and 0 <= y and y < m;
    };

    vector<pair<int, int>> dxdy = {
        {0, +1}, {0, -1}, {+1, 0}, {-1, 0}
    };

    while(!q.empty()) {
        auto u = q.front(); q.pop();
        int x = u[0], y = u[1];
        for(auto& [dx, dy]: dxdy) {
            int nx = x + dx, ny = y + dy;
            if(ok(nx, ny) and d[nx][ny] == -1 and S[nx][ny] - 1 <= S[x][y]) {
                d[nx][ny] = d[x][y] + 1;
                cout << "x = " << x << ", y = " << y << '\n';
                cout << "nx = " << nx << ", ny = " << ny << '\n';
                cout << "nd = " << d[nx][ny] << ", d = " << d[x][y] << '\n'; 
                q.push({nx, ny});
            } 
        }
    }
    cout << d[ed[0]][ed[1]] << '\n';

    return 0;
}
