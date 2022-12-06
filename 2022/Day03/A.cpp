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
    for(int _ = 0; _ < N; _++) {
        string a; cin >> a;
        int n = (int)a.size();
        set<char> seen;
        for(int i = 0; i < n / 2; i++) {
            seen.insert(a[i]);
        }
        for(int i = n / 2; i < n; i++) {
            if(seen.find(a[i]) != seen.end()) {
                if('A' <= a[i] and a[i] <= 'Z') {
                    ans += a[i] - 'A' + 27;
                    break;
                } 
                if('a' <= a[i] and a[i] <= 'z') {
                    ans += a[i] - 'a' + 1;
                    break;
                }
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
