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
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(S[i][j] == 'S') st = {i, j};
            if(S[i][j] == 'E') ed = {i, j};
        }
    }
    
    auto ok = [&](int x, int y) -> bool {
        return 0 <= x and x < n and 0 <= y and y < m;
    };

    vector<pair<int, int>> dxdy = {
        {0, +1}, {0, -1}, {+1, 0}, {-1, 0}
    };

    vector<vector<int>> d(n, vector<int>(m, -1));
    d[st[0]][st[1]] = 0;
    queue<array<int, 2>> q;
    q.push(st);
    S[st[0]][st[1]] = 'a';
    S[ed[0]][ed[1]] = 'z';
    while(!q.empty()) {
        auto u = q.front(); q.pop();
        int x = u[0], y = u[1];
        for(auto& [dx, dy]: dxdy) {
            int nx = x + dx, ny = y + dy;
            if(ok(nx, ny) and d[nx][ny] == -1 and S[nx][ny] - 1 <= S[x][y]) {
                d[nx][ny] = d[x][y] + 1;
                q.push({nx, ny});
            } 
        }
    }
    cout << d[ed[0]][ed[1]] << '\n';

    return 0;
}
