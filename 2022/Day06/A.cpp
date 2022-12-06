#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define dbg(...)
#endif

void solve() {
    string s; cin >> s;
    const int n = (int)s.size();
    vector<vector<int>> a(n, vector<int>(26, 0));
    for(int i = 0; i < n; i++) {
        a[i][s[i] - 'a']++;
        for(int j = 0; j < 26; j++) {
            a[i][j] += (i - 1 >= 0? a[i - 1][j]: 0);
        }
    }
    auto query = [&](int L, int R) -> int {
        int cnt = 0;
        for(int i = 0; i < 26; i++) {
            cnt += (a[R][i] - (L - 1 >= 0? a[L - 1][i]: 0)) == 1;
        }
        return cnt;
    };
    for(int i = 0; i < n; i++) {
        if(i + 3 < n) {
            if(query(i, i + 3) == 4) {
                cout << i + 4 << '\n';
                return;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifdef LOCAL
    freopen("error.txt", "w", stderr);
#endif

    int T = 1;
    for(int tc = 1; tc <= T; tc++) {
        // cout << "Case #" << tc << ": ";
        solve();
    }

    return 0;
}
