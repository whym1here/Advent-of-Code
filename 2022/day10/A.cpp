#include <bits/stdc++.h>
using namespace std;

vector<string> readlines() {
    string s;
    vector<string> S;
    while(getline(cin, s) and (int)s.size() > 0) S.push_back(s);
    return S;
}

vector<string> split(string s) {
    stringstream ss(s);
    vector<string> S;
    while(ss >> s) S.push_back(s);
    return S;
}

int main() {
    vector<string> S = readlines();
    const int N = (int)S.size();

    int X = 1;
    int C = 0; 
    
    auto f = [&](int C) -> bool {
        for(int e: {20, 60, 100, 140, 180, 220}) {
            if(C == e) return true;
        }
        return false;
    };
    
    int ans = 0;
    for(int _ = 0; _ < N; _++) {
        if(S[_][0] == 'n') {
            C++;
            if(f(C)) ans += C * X;
        } else {
            vector<string> s = split(S[_]);
            int V = stoi(s[1]); 
            
            C++; 
            if(f(C)) ans += C * X;
            
            C++;
            if(f(C)) ans += C * X;
            X += V;
        }
    }  
    cout << ans << '\n';

    return 0;
}
