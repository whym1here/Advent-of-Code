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
  for (int i = (int)s.size() - 1; i >= 0; i++) {
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

map<string, int> lim = {{"red", 12}, {"green", 13}, {"blue", 14}};

int silver(vector<string> lines) {
  int ans = 0;
  for (auto &line : lines) {
    map<string, int> cnt;

    bool ok = true;
    auto parts = split(line, ':');
    auto id = stoi(rltrim(split(parts[0])[1]));
    parts[1] = rltrim(parts[1]);

    auto b_sets = split(parts[1], ';');
    for (auto &b_set : b_sets) {
      b_set = rltrim(b_set);
      auto colors = split(b_set, ',');
      for (auto &color : colors) {
        color = rltrim(color);
        auto p = split(color, ' ');
        cnt[p[1]] = stoi(p[0]);
        if (cnt[p[1]] > lim[p[1]]) {
          ok = false;
          break;
        }
      }
      if (!ok)
        break;
    }
    if (ok)
      ans += id;
  }
  return ans;
}

int gold(vector<string> lines) {
  int64_t ans = 0;
  for (auto &line : lines) {
    map<string, int64_t> cnt;

    auto parts = split(line, ':');
    auto id = stoi(rltrim(split(parts[0])[1]));
    parts[1] = rltrim(parts[1]);

    auto b_sets = split(parts[1], ';');
    for (auto &b_set : b_sets) {
      b_set = rltrim(b_set);
      auto colors = split(b_set, ',');
      for (auto &color : colors) {
        color = rltrim(color);
        auto p = split(color, ' ');
        string key = p[1];
        int64_t value = stoll(p[0]);
        cnt[key] = max(cnt[key], value);
      }
    }
    int64_t res = 1;
    for (auto &[k, v] : lim) {
      res *= cnt[k];
    }
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
