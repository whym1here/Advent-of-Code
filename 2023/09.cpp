#include <bits/stdc++.h>
using namespace std;

vector<string> read_lines(string file_name = "input.txt") {
  vector<string> res;
  string line;
  ifstream file(file_name);
  if (file.is_open()) {
    while (getline(file, line)) {
      res.push_back(line);
    }
    file.close();
  }
  return res;
}

vector<string> split(string s, char c = ' ') {
  vector<string> res;
  string cur = "";
  for (char ch : s) {
    if (ch == c) {
      if (!cur.empty())
        res.push_back(cur);
      cur = "";
    } else {
      cur += ch;
    }
  }
  if (!cur.empty()) {
    res.push_back(cur);
  }
  return res;
}

string rltrim(string s, char c = ' ') {
  int lo = -1, hi = -1;
  for (int i = 0; i < (int)s.size(); i++) {
    if (s[i] != c) {
      lo = i;
      break;
    }
  }
  for (int i = (int)s.size() - 1; i >= 0; i--) {
    if (s[i] != c) {
      hi = i;
      break;
    }
  }
  if (lo != -1 and hi != -1) {
    string res = "";
    for (int i = lo; i <= hi; i++)
      res += s[i];
    return res;
  }
  return "";
}

int64_t silver(vector<string> lines) {
  int64_t ans = 0;
  for (auto &line : lines) {
    auto values = split(line);

    vector<int64_t> a;
    for (auto &e : values)
      a.emplace_back(stoll(e));

    vector<int64_t> cur = a, nxt;
    vector<int64_t> lasts = {cur.back()};

    while (cur.size() != 1) {
      nxt.clear();
      const int n = (int)cur.size();
      for (int i = 1; i < n; i++)
        nxt.push_back(cur[i] - cur[i - 1]);
      cur = nxt;
      lasts.push_back(cur.back());
    }

    int len = (int)lasts.size();
    for (int i = len - 2; i >= 0; i--) {
      lasts[i] += lasts[i + 1];
    }

    ans += lasts.front();
  }

  return ans;
}

int64_t gold(vector<string> lines) {
  int64_t ans = 0;
  for (auto &line : lines) {
    auto values = split(line);

    vector<int64_t> a;
    for (auto &e : values)
      a.emplace_back(stoll(e));

    vector<int64_t> cur = a, nxt;
    vector<int64_t> firsts = {cur.front()};

    while (cur.size() != 1) {
      nxt.clear();
      const int n = (int)cur.size();
      for (int i = 1; i < n; i++)
        nxt.push_back(cur[i] - cur[i - 1]);
      cur = nxt;
      firsts.push_back(cur.front());
    }

    int len = (int)firsts.size();
    for (int i = len - 2; i >= 0; i--) {
      firsts[i] -= firsts[i + 1];
    }

    ans += firsts.front();
  }

  return ans;
}

int main() {
  vector<string> lines = read_lines();
  cout << silver(lines) << '\n';
  cout << gold(lines) << '\n';
  return 0;
}
