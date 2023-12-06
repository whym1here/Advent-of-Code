#include <bits/stdc++.h>
using namespace std;

vector<string> read_lines() {
  vector<string> res;
  string str;
  while (true) {
    getline(cin, str);
    if (str.size() == 0)
      break;
    res.push_back(str);
  }
  return res;
}

vector<string> split(string s, char c = ' ') {
  vector<string> res;
  string cur = "";
  for (char ch : s) {
    if (ch == c) {
      if (cur.size() > 0)
        res.push_back(cur);
      cur = "";
    } else {
      cur += ch;
    }
  }
  if (cur.size() > 0) {
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

vector<pair<int, int>> dxy = {{0, 1},   {0, -1}, {1, 0},  {-1, 0},
                              {-1, -1}, {1, -1}, {-1, 1}, {1, 1}};

int64_t silver(vector<string> lines) {
  auto &a = lines;
  for (auto &e : a) {
    e = rltrim(e);
    e = rltrim(e, '\n');
  }
  const int n = (int)a.size(), m = (int)a[0].size();
  int64_t ans = 0;

  auto ok = [&](int x, int y) -> bool {
    return 0 <= x and x < n and 0 <= y and y < m;
  };

  auto sim = [&](char c) -> bool {
    return !('0' <= c and c <= '9') and c != '.';
  };

  for (int i = 0; i < n; i++) {
    string s = "";
    bool pos = false;
    for (int j = 0; j < m; j++) {
      char c = a[i][j];
      if ('0' <= c and c <= '9') {
        s += c;
        if (!pos) {
          for (auto &[dx, dy] : dxy) {
            int nx = i + dx, ny = j + dy;
            if (ok(nx, ny) and sim(a[nx][ny])) {
              pos = true;
              break;
            }
          }
        }
      } else if (!s.empty()) {
        if (pos)
          ans += stoll(s);
        s.clear();
        pos = false;
      }
    }
    if (!s.empty()) {
      if (pos)
        ans += stoll(s);
      s.clear();
      pos = false;
    }
  }

  return ans;
}

int gold(vector<string> lines) {
  auto &a = lines;
  for (auto &e : a) {
    e = rltrim(e);
    e = rltrim(e, '\n');
  }
  const int n = (int)a.size(), m = (int)a[0].size();
  int64_t ans = 0;

  auto ok = [&](int x, int y) -> bool {
    return 0 <= x and x < n and 0 <= y and y < m;
  };

  auto sim = [&](char c) -> bool {
    return !('0' <= c and c <= '9') and c != '.';
  };

  map<pair<int, int>, vector<int64_t>> cnt;

  for (int i = 0; i < n; i++) {
    string s = "";
    set<pair<int, int>> p;
    for (int j = 0; j < m; j++) {
      char c = a[i][j];
      if ('0' <= c and c <= '9') {
        s += c;
        for (auto &[dx, dy] : dxy) {
          int nx = i + dx, ny = j + dy;
          if (ok(nx, ny) and a[nx][ny] == '*') {
            p.emplace(nx, ny);
          }
        }
      } else if (!s.empty()) {
        for (auto &e : p)
          cnt[e].push_back(stoll(s));
        s.clear();
        p.clear();
      }
    }
    if (!s.empty()) {
      for (auto &e : p)
        cnt[e].push_back(stoll(s));
      s.clear();
      p.clear();
    }
  }

  for (auto &[k, v] : cnt) {
    if (v.size() == 2) {
      ans += v[0] * 1LL * v[1];
    }
  }

  return ans;
}

int main() {
  vector<string> lines = read_lines();
  cout << silver(lines) << '\n';
  cout << gold(lines) << '\n';
  return 0;
}
