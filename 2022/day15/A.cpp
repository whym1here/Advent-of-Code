#include <bits/stdc++.h>
using namespace std;

vector<string> readlines() {
    string s;
    vector<string> S;
    while(getline(cin, s) and (int)s.size() > 0) S.push_back(s);
    return S;
}

vector<string> split(string s) {
    vector<string> S;
    stringstream ss(s);
    while(ss >> s) S.push_back(s);
    return S;
}

void replace(string& S, char cur, char nxt) {
    const int n = (int)S.size();
    for(int i = 0; i < n; i++) {
        if(S[i] == cur) S[i] = nxt;
    }
}

void main() {
    auto lines = readlines();


    return 0;
}
