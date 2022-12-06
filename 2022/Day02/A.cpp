#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    
    map<char, char> mp;
    mp['X'] = 'A';
    mp['Y'] = 'B';
    mp['Z'] = 'C';
    
    int ans = 0;
    for(int _ = 0; _ < n; _++) {
        char x, y; cin >> x >> y;
        int a = x - 'A', b = -1;
        if(y == 'X') {
            b = (3 + a - 1) % 3;
        } else if(y == 'Y') {
            b = a;
            ans += 3;
        } else {
            b = (a + 1) % 3;
            ans += 6;
        }
        ans += b + 1;
    }
    cout << ans << '\n';

    return 0;
}
