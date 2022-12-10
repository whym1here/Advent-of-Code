#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<vector<int>> a;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        vector<int> x;
        for(char c: s) x.push_back(c - '0');
        a.push_back(x);
    }
    int m = (int)a[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    
    auto ok = [&](int x, int y) -> bool {
        return 0 <= x and x < n and 0 <= y and y < m;
    };

    auto dfs = [&](int x, int y, int dx, int dy) -> void {
        int mx = a[x][y];
        vis[x][y] = true;
        while(ok(x, y)) {
            if(a[x][y] > mx) {
                mx = a[x][y];
                vis[x][y] = true; 
            }
            x += dx, y += dy;
        }
    };

    for(int i = 0; i < n; i++) {
        dfs(i, 0, 0, 1);
        dfs(i, m - 1, 0, -1);
    }

    for(int i = 0; i < m; i++) {
        dfs(0, i, 1, 0);
        dfs(n - 1, i, -1, 0);
    }

    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            ans += vis[i][j];
        }
    }

    cout << ans << '\n';
    
    return 0;
}
