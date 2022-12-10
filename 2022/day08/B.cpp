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
    
    auto ok = [&](int x, int y) -> bool {
        return 0 <= x and x < n and 0 <= y and y < m;
    };

    auto dfs = [&](int x, int y, int dx, int dy) -> int {
        int mx = a[x][y];
        int X = x, Y = y;
        int stx = x, sty = y;
        int cnt = 0;
        bool found = false;
        int vx = x, vy = y;
        while(ok(x, y)) {
            if(x == stx and y == sty) {
                x += dx, y += dy;
                continue;
            }
            if(a[x][y] >= mx) {
                mx = a[x][y];
                X = x, Y = y;
                found = true;
                break;
            }
            vx = x, vy = y;
            x += dx, y += dy;
        } 
        return (found? abs(stx - X) + abs(sty - Y): abs(stx - vx) + abs(sty - vy));
    };

    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            ans = max(ans, dfs(i, j, 0, 1) * dfs(i, j, 0, -1) * dfs(i, j, 1, 0) * dfs(i, j, -1, 0)); 
        } 
    }

    cout << ans << '\n';
    
    return 0;
}
