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
    vector<char> F;
        
    auto check = [](int X, int C) -> bool {
        return X == (C % 40) or X == (C - 1 + 40) % 40 or X == (C + 1) % 40;
    };

    for(int _ = 0; _ < N; _++) {
        if(S[_][0] == 'n') {
            if(check(X, C)) F.push_back('#');
            else F.push_back('.');
            C++;
        } else {
            vector<string> s = split(S[_]);
            int V = stoi(s[1]);
            
            if(check(X, C)) F.push_back('#');
            else F.push_back('.');
            C++; 
            
            if(check(X, C)) F.push_back('#');
            else F.push_back('.');        
            C++;
            X += V;
        }
    }
    
    for(int i = 0; i < (int)F.size(); i++) {
        if(i % 40 == 0) cout << '\n';
        cout << F[i];
    }

    return 0;
}
