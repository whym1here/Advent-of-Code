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

int64_t solver(string s, vector<int64_t> a) {
  const int n = (int)s.size(), m = (int)a.size();
  vector<int> p(n, 0);
  for (int i = 0; i < n; i++) {
    p[i] = (s[i] == '.') + (i - 1 >= 0 ? p[i - 1] : 0);
  }
  vector<vector<int64_t>> dp(n + 1, vector<int64_t>(m + 1, -1));

  function<int64_t(int, int)> f = [&](int i, int j) -> int64_t {
    if (i == n)
      return j == m;

    int64_t &ans = dp[i][j];
    if (ans != -1)
      return ans;

    ans = 0;

    if (s[i] != '#')
      ans += f(i + 1, j);

    if (j < m) {
      int len = a[j];
      if (i + len - 1 < n and p[i + len - 1] == (i - 1 >= 0 ? p[i - 1] : 0)) {
        if (i + len == n and j + 1 == m) {
          ans += 1;
        } else if (i + len < n and s[i + len] != '#') {
          ans += f(i + len + 1, j + 1);
        }
      }
    }
    return ans;
  };

  return f(0, 0);
}

int64_t silver(vector<string> lines) {
  int64_t ans = 0;
  vector<pair<string, vector<int64_t>>> a;

  for (auto &line : lines) {
    auto parts = split(line);
    a.emplace_back(parts[0], vector<int64_t>());
    for (auto &e : split(parts[1], ',')) {
      a.back().second.push_back(stoll(rltrim(e)));
    }
  }

  for (auto &[s, v] : a) {
    int64_t res = solver(s, v);
    ans += res;
  }

  return ans;
}

int64_t gold(vector<string> lines) {
  int64_t ans = 0;
  vector<pair<string, vector<int64_t>>> a;

  for (auto &line : lines) {
    auto parts = split(line);
    string s = parts[0];
    a.emplace_back("", vector<int64_t>());
    vector<int64_t> values;
    for (auto &e : split(parts[1], ',')) {
      values.push_back(stoll(rltrim(e)));
    }
    int t = 5;
    while (t--) {
      a.back().first += s + (t != 0 ? "?" : "");
      for (auto &value : values)
        a.back().second.push_back(value);
    }
  }

  for (auto &[s, v] : a) {
    int64_t res = solver(s, v);
    ans += res;
  }

  return ans;
}

int main() {
  vector<string> lines = read_lines();
  cout << silver(lines) << '\n';
  cout << gold(lines) << '\n';
  return 0;
}
