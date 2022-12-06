#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define dbg(...)
#endif

void solve() {
    int N; cin >> N;
    int ans = 0;
    for(int _ = 0; _ < N / 3; _++) {
        vector<string> a(3);
        for(int i = 0; i < 3; i++) cin >> a[i];
        vector<vector<int>> cnt(3, vector<int>(26 * 2, 0));
        for(int i = 0; i < 3; i++) {
            for(char c: a[i]) {
                if('a' <= c and c <= 'z') {
                    cnt[i][c - 'a']++;
                }
                if('A' <= c and c <= 'Z') {
                    cnt[i][c - 'A' + 26]++;
                }
            }
        }
        for(int i = 0; i < 26 * 2; i++) {
            if(cnt[0][i] and cnt[1][i] and cnt[2][i]) {
                ans += i + 1;
            }
        }
    }
    cout << ans << '\n';
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
